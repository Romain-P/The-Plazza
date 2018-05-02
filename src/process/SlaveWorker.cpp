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
#include "SlaveWorker.h"

void SlaveWorker::search(std::vector<std::string> &files, std::string &pattern) {
    tick();
    remove_invalid_files(files);

    auto task = [this, pattern](std::string &filename) mutable {
        std::ifstream input(filename);

        std::regex rgx(pattern);
        for(std::string line; getline(input, line);)
            analyse_file_line(line, pattern, rgx);

        _client->send(FreePlaceMessage(1));
    };
    for (auto &file: files) {
        task_t bind = std::bind(task, file);
        _workers.execute(bind);
    }
}

void SlaveWorker::stop() {
    _workers.stop();
    _workers.await_stop();
    _client->stop();
    _timer.stop();
    _timer.getThread().join();
}

bool SlaveWorker::remove_invalid_files(std::vector<std::string> &files) {
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

void SlaveWorker::analyse_file_line(std::string &line, std::string &pattern, std::regex &rgx) {
    std::smatch matcher;
    std::string::const_iterator it(line.cbegin());
    while (std::regex_search(it, line.cend(), matcher, rgx)) {
        std::string match(matcher[0]);
        _client->send(SearchResultMessage(match, pattern));
        it += matcher.position() + matcher.length();
    }
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