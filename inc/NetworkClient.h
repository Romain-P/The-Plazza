//
// Created by romain.pillot on 4/19/18.
//

#ifndef PLAZZA_NETWORKCLIENT_HPP
#define PLAZZA_NETWORKCLIENT_HPP

#include <thread>
#include <mutex>
#include <memory>
#include "Shared.h"
#include "NetworkBuffer.h"

class NetworkClient {
public:
    static std::unique_ptr<NetworkClient> create(session_t session);
    explicit NetworkClient(session_t session) : _session(session),
                                                _thread(),
                                                _locker(),
                                                _running(true),
                                                _buffer(),
                                                _packet_length(0),
                                                _read(0)
    {}

    void stop();
private:
    session_t _session;
    std::thread _thread;
    std::shared_mutex _locker;
    bool _running;
    NetworkBuffer _buffer;
    int32_t _packet_length;
    int32_t _read;

    void init();
    bool running();
    void close_connection();
    void process_data(char *data, ssize_t length);
};

#endif //PLAZZA_NETWORKCLIENT_HPP
