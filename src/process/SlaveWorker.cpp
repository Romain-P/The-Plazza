//
// Created by romain on 28/04/18.
//

#include <sys/stat.h>
#include <fstream>
#include <chrono>
#include <regex>
#include <SearchResultMessage.h>
#include <FreePlaceMessage.h>
#include <DestroyProcessMessage.h>
#include <XorCipher.h>
#include "SlaveWorker.h"

void SlaveWorker::search(std::vector<std::string> &files, std::string const &pattern) {
    tick();
    remove_invalid_files(files);

    for (auto &file: files)
        process_file(file, pattern);
}

void SlaveWorker::process_file(std::string const &file, std::string const &pattern) {
    auto task = [this, pattern](std::string const &filename) mutable {
        std::ifstream input(filename);

        std::regex rgx(pattern);
        for(std::string line; getline(input, line);)
            analyse_file_line(line, pattern, rgx);

        _client->send(FreePlaceMessage(1));
    };
    task_t bind = std::bind(task, file);
    _workers.execute(bind);
}

void SlaveWorker::stop() {
    _workers.stop();
    _workers.await_stop();
    _client->stop();
    _timer.stop();
    _timer.getThread().join();
}

void SlaveWorker::remove_invalid_files(std::vector<std::string> &files) {
    struct stat s {};

    std::vector<std::string> cpy(files);
    files.clear();
    for(auto &file: cpy) {
        if (!stat(file.c_str(), &s))
            files.push_back(file);
    }
    auto free_place = static_cast<int32_t>(cpy.size() - files.size());
    if (free_place)
        _client->send(FreePlaceMessage(free_place));
}

void SlaveWorker::analyse_file_line(std::string &line, std::string const &pattern, std::regex const &rgx, bool ciphered) {
    bool matched = false;

    if (ciphered) {
        XorCipher::bruteforce(line, [this, &pattern, &rgx](std::string &reversed) {
            return find_matches(reversed, pattern, rgx);
        });
    } else
        matched = matched || find_matches(line, pattern, rgx);

    if (!matched && !ciphered && XorCipher::maybeCiphered(line))
        analyse_file_line(line, pattern, rgx, true);
}

bool SlaveWorker::find_matches(std::string const &line, std::string const &pattern, std::regex const &rgx) {
    std::smatch matcher;
    std::string::const_iterator it(line.cbegin());
    bool matched = false;

    while (std::regex_search(it, line.cend(), matcher, rgx)) {
        std::string match(matcher[0]);
        _client->send(SearchResultMessage(match, pattern));
        it += matcher.position() + matcher.length();
        matched = true;
    }
    return matched;
}

void SlaveWorker::init() {
    enable_timout();
    _workers.init();
}

void SlaveWorker::tick() {
    _last_tick = current_time();
}

void SlaveWorker::enable_timout() {
    _timer = Timer([this]() mutable {
        if (_workers.working())
            _last_tick = current_time();
        else if (current_time() - _last_tick >= 5000) {
            _client->send(DestroyProcessMessage(false));
            _timer.stop();
        }
    }, std::chrono::duration<ssize_t>(std::chrono::seconds(1)));

    _timer.start();
}

millis_t SlaveWorker::current_time() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

void SlaveWorker::workAndStop() {
    while (_workers.working());
    stop();
}

