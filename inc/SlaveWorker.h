//
// Created by romain on 28/04/18.
//

#ifndef PLAZZA_SLAVEWORKER_H
#define PLAZZA_SLAVEWORKER_H


#include <string>
#include <vector>
#include "NetworkClient.h"

class SlaveWorker {
public:
    SlaveWorker(NetworkClient *client) : _client(client) {}

    void search(std::vector<std::string> &files, std::string &pattern);

private:
    NetworkClient *_client;
};


#endif //PLAZZA_SLAVEWORKER_H
