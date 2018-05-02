//
// Created by romain on 28/04/18.
//

#ifndef PLAZZA_SLAVEWORKER_H
#define PLAZZA_SLAVEWORKER_H


#include <string>
#include <vector>
#include <regex>
#include "NetworkClient.h"
#include "ThreadPoolExecutor.h"
#include "Timer.h"

using millis_t = ssize_t;

class SlaveWorker {
public:
    SlaveWorker(NetworkClient *client, size_t threads) : _client(client), _workers(threads), _last_tick(0), _timer() {}

    void init();
    void search(std::vector<std::string> &files, std::string &pattern);
    void stop();

    /**
     * Execute in progress and pending tasks, and then exit the slave
     * Thread Blocking function
     */
    void workAndStop();
private:
    NetworkClient *_client;
    ThreadPoolExecutor _workers;
    ssize_t _last_tick;
    Timer _timer;

    void remove_invalid_files(std::vector<std::string> &files);
    void analyse_file_line(std::string &line, std::string &pattern, std::regex &rgx);
    void enable_timout();
    void tick();
    millis_t current_time();
};


#endif //PLAZZA_SLAVEWORKER_H
