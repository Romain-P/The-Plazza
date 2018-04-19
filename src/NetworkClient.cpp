//
// Created by romain.pillot on 4/19/18.
//

#include "NetworkClient.h"

std::unique_ptr<NetworkClient> NetworkClient::create(session_t session) {
    auto client = std::make_unique<NetworkClient>(session);
    client->_thread = std::thread(&NetworkClient::init, client.get());
    return std::move(client);
}

void NetworkClient::init() {
    while (running()) {
        //TODO: recv
    }
    close_connection();
}

void NetworkClient::stop() {
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


void NetworkClient::close_connection() {
    shutdown(_session, SHUT_RDWR);
    close_socket(_session);
}
