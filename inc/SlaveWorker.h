//
// Created by romain on 28/04/18.
//

#ifndef PLAZZA_SLAVEWORKER_H
#define PLAZZA_SLAVEWORKER_H


#include <string>
#include <vector>
#include "NetworkClient.h"
#include "ThreadPoolExecutor.h"

class SlaveWorker {
public:
    SlaveWorker(NetworkClient *client, size_t threads) : _client(client), _workers(threads) {}

    void search(std::vector<std::string> &files, std::string const &pattern);
    void stop();
private:
    NetworkClient *_client;
    ThreadPoolExecutor _workers;
};


#endif //PLAZZA_SLAVEWORKER_H
