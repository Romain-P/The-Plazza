//
// Created by romain.pillot on 4/19/18.
//

#include "NetworkClient.h"
#include <iostream>
#include <memory>

std::unique_ptr<NetworkClient> NetworkClient::create(session_t session) {
    auto client = std::make_unique<NetworkClient>(session);
    client->_thread = std::thread(&NetworkClient::init, client);
    return std::move(client);
}

void NetworkClient::init() {
    while (running()) {
        //TODO: recv
    }
}

void NetworkClient::close() {
    _locker.lock();
    _running = false;
    _locker.unlock();
}

bool NetworkClient::running() {
    bool running;
    _locker.lock();
    running = _running;
    _locker.unlock();
    return running;
}
