//
// Created by romain.pillot on 4/19/18.
//

#ifndef PLAZZA_NETWORKCLIENT_HPP
#define PLAZZA_NETWORKCLIENT_HPP

#include <thread>
#include <mutex>
#include "Shared.h"

class NetworkClient {
public:
    static std::unique_ptr<NetworkClient> create(session_t session);
    explicit NetworkClient(session_t session) : _session(session), _thread(), _locker(), _running() {}

    void close();
private:
    session_t _session;
    std::thread _thread;
    std::mutex _locker;
    bool _running;

    void init();
    bool running();
};

#endif //PLAZZA_NETWORKCLIENT_HPP
