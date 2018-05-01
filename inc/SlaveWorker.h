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

class SlaveWorker {
public:
    SlaveWorker(NetworkClient *client, size_t threads) : _client(client), _workers(threads) {}

    void init();
    void search(std::vector<std::string> &files, std::string &pattern);
    void stop();
private:
    NetworkClient *_client;
    ThreadPoolExecutor _workers;

    bool remove_invalid_files(std::vector<std::string> &files);
    void analyse_file_line(std::string &line, std::string &pattern, std::regex &rgx);
};


#endif //PLAZZA_SLAVEWORKER_H
