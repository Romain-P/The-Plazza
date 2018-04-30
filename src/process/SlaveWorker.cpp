//
// Created by romain on 28/04/18.
//

#include "SlaveWorker.h"

void SlaveWorker::search(std::vector<std::string> &files, std::string const &pattern) {
    //TODO: thread pool
}

void SlaveWorker::stop() {
    _workers.stop();
    _workers.await_stop();
    _client->stop();
    _client->await_stop();
}
