//
// Created by romain on 26/04/18.
//

#include <spawn.h>
#include <unistd.h>
#include <cstring>
#include "SearchRequestMessage.h"
#include "TaskDispatcher.h"

constexpr char TaskDispatcher::SLAVE_MOD[];

const std::unordered_map<std::string, std::string> TaskDispatcher::_patterns = {
        { "PHONE_NUMBER", "^0\\s*[1-9](?:[\\s.-]*\\d{2}){4}$" },
        { "EMAIL_ADDRESS", "[a-zA-Z0-9_.-]+@[a-zA-Z0-9_.-]+" },
        { "IP_ADDRESS", "[0-255].[0-255].[0-255].[0-255]" }
};

void TaskDispatcher::parse_commands(std::string &line) {
    lock_t lock(_locker);

    std::vector<std::string> commands = util::split(const_cast<char *>(line.c_str()), ";");

    for (auto &command: commands) {
        files_t files = util::split(const_cast<char *>(line.c_str()), " ");
        std::string const &pattern = _patterns.at(files.back());
        files.pop_back();

        dispatch(files, pattern);
    }
}

void TaskDispatcher::dispatch(files_t &files, std::string const &pattern) {
    size_t tasks_count = files.size();
    std::map<process_t, size_t> config;

    while (tasks_count && find_places(config, tasks_count));

    if (tasks_count) {
        create_new_process();
        put_on_hold(files, pattern, tasks_count);
    }

    for (auto &keyset: config) {
        process_t slave = keyset.first;
        size_t file_count = keyset.second;

        send_task(slave, files, file_count, pattern);
    }
}

bool TaskDispatcher::find_places(std::map<process_t, size_t> &config, size_t tasks) {
    bool all_busy = true;

    for(auto keyset = _processes.begin(); keyset != _processes.end() && tasks; ++keyset) {
        process_t process = keyset->first;
        free_places places = keyset->second;

        if (places) {
            if (config.find(process) == config.end())
                config[process] = 1;
            else
                config[process] = config[process] + 1;
            --tasks;
            all_busy = false;
        }
    }
    return !all_busy;
}

void TaskDispatcher::create_new_process() {
    pid_t child;
    char const *plazza_path = _slave_args[0];
    int32_t error;

    if ((error = posix_spawn(&child, plazza_path, nullptr, nullptr, _slave_args, environ))) {
        fprintf(stderr, "TaskManager: cant fork: %s\n", strerror(error));
        exit(1);
    }
}

void TaskDispatcher::put_on_hold(files_t &files, std::string const &pattern, size_t file_count) {
    files_t awaiting_files(files);

    awaiting_files.erase(awaiting_files.begin(), awaiting_files.end() - file_count);
    files.erase(files.end() - file_count, files.end());

    _pending_tasks.emplace_back(pattern, awaiting_files);
}

void TaskDispatcher::send_task(process_t process, files_t &files, size_t count, std::string const &pattern) {
    files_t list(files.begin(), files.begin() + count);
    files.erase(files.begin(), files.begin() + count);
    _network->getClients()[process]->send(SearchRequestMessage(files, pattern));
}

void TaskDispatcher::refresh_free_places(process_t p, free_places count) {
    lock_t lock(_locker);

    if (_processes.find(p) == _processes.end())
        _processes[p] = count;
    else
        _processes[p] = _processes[p] + count;

    for (Task &task: _pending_tasks)
        dispatch(task.getFiles(), task.getRegex());
}