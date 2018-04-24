//
// Created by romain.pillot on 4/19/18.
//

#include <NetworkProtocol.h>
#include <AbstractPacketHandler.h>
#include "NetworkClient.h"

std::unique_ptr<NetworkClient> NetworkClient::create(session_t session, AbstractPacketHandler *handler) {
    auto client = std::make_unique<NetworkClient>(session, handler);
    client->init();
    return client;
}

std::thread &NetworkClient::init(bool first) {
    if (first) {
        _thread = std::thread(&NetworkClient::init, this, false);
    } else
        run();
    return _thread;
}

void NetworkClient::run() {
    uint8_t buffer[1024];

    while (running()) {
        ssize_t bytes = recv(_session, buffer, 1024, 0);
        buffer[bytes] = 0;
        process_data(buffer, bytes);
    }
    close_connection();
}

void NetworkClient::process_data(uint8_t *buffer, ssize_t length) {
    ssize_t diff = 0;
    ssize_t next_length = 0;
    ssize_t next_begin = 0;

    if (!_packet_length) {
        _packet_length = NetworkProtocol::packet_length(buffer);
        diff = NetworkProtocol::LENGTH_BYTES;
    }
    bool next_began = _read + length > _packet_length;
    if (next_began)
        diff += (next_length = _read + length - _packet_length);
    next_begin = length - diff;
    _buffer.push_bytes(buffer, next_begin);
    _read += next_begin;
    if (_read == _packet_length) {
        std::unique_ptr<NetworkMessage> message;
        try {
            message = std::move(NetworkProtocol::build_packet(_buffer));
            _handler->parse_packet(this, message.get());
        } catch(std::exception &e) {
            fprintf(stderr, "client %d: %s", _session, e.what());
        }
        _buffer.clear();
        _packet_length = 0;
        _read = 0;
        if (next_began)
            process_data(buffer + next_begin, next_length);
    }
}

void NetworkClient::stop() {
    write_lock_t lock(_locker);

    _running = false;
}

bool NetworkClient::running() {
    read_lock_t lock(_locker);

    return _running;
}


void NetworkClient::close_connection() {
    shutdown(_session, SHUT_RDWR);
    close_socket(_session);
}