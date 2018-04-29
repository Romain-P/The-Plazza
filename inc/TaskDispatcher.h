//
// Created by romain on 26/04/18.
//

#ifndef PLAZZA_PROCESSMANAGER_H
#define PLAZZA_PROCESSMANAGER_H

#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include "NetworkServer.h"
#include "Task.h"
#include <regex>

using process_t = session_t;
using free_places = ssize_t;
using files_t = std::vector<std::string>;
using free_processes_t = std::vector<process_t>;

class TaskDispatcher {
public:
    static constexpr char SLAVE_MOD[] = "slavemode";

    /**
     *
     * @param network           network server
     * @param threadpool_size   threads per slave
     */
    explicit TaskDispatcher(NetworkServer &network, std::string &threadpool_size, std::string &serverPort, char *binary_path) :
            _processes(),
            _locker(),
            _pending_tasks(),
            _network(&network),
            _slave_args {
                                binary_path,
                                const_cast<char *>(SLAVE_MOD),
                                &serverPort[0],
                                &threadpool_size[0],
                                nullptr
            },
            _slave_maxtasks(static_cast<size_t>(atoi(&threadpool_size[0])) * 2)
    {}

    void parse_commands(std::string &line);
    void refresh_free_places(process_t p, free_places count);
    bool remains_tasks();

private:
    static const std::unordered_map<std::string, std::string> _patterns;
    static const std::regex CMD_PATTERN;
    static const std::regex FILE_PATTERN;

    std::unordered_map<process_t, free_places> _processes;
    std::mutex _locker;
    std::vector<Task> _pending_tasks;
    NetworkServer *_network;
    char *_slave_args[5];
    size_t _slave_maxtasks;

    void dispatch(files_t &files, std::string const &pattern);
    bool find_places(std::map<process_t, size_t> &config, size_t &tasks);
    void create_new_process();
    void put_on_hold(files_t &files, std::string const &pattern, size_t file_count);
    void send_task(process_t, files_t &files, size_t count, std::string const &pattern);
};

#endif //PLAZZA_PROCESSMANAGER_H
