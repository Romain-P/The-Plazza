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
    explicit TaskDispatcher(NetworkServer &network, size_t threadpool_size, char *binary_path) :
            _processes(),
            _locker(),
            _pending_tasks(),
            _threadpool_size(threadpool_size),
            _network(&network),
            _slave_args {
                                binary_path,
                                const_cast<char *>(std::to_string(network.getPort()).c_str()),
                                const_cast<char *>(std::to_string(threadpool_size).c_str()),
                                nullptr
            }
    {}

    void parse_commands(std::string &line);
    void refresh_free_places(process_t p, free_places count);

private:
    static const std::unordered_map<std::string, std::string> _patterns;

    std::unordered_map<process_t, free_places> _processes;
    std::mutex _locker;
    std::vector<Task> _pending_tasks;
    size_t _threadpool_size;
    NetworkServer *_network;
    char *_slave_args[4];

    void dispatch(files_t &files, std::string const &pattern);
    bool find_places(std::map<process_t, size_t> &config, size_t tasks);
    void create_new_process();
    void put_on_hold(files_t &files, std::string const &pattern, size_t file_count);
    void send_task(process_t, files_t &files, size_t count, std::string const &pattern);
};

#endif //PLAZZA_PROCESSMANAGER_H
