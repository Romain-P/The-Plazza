//
// Created by romain.pillot on 4/19/18.
//

#include <NetworkProtocol.h>
#include <AbstractPacketHandler.h>
#include "NetworkClient.h"

std::unique_ptr<NetworkClient> NetworkClient::create(session_t session) {
    auto client = std::make_unique<NetworkClient>(session);
    client->_thread = std::thread(&NetworkClient::init, client.get());
    return std::move(client);
}

void NetworkClient::init() {
    char buffer[1024];

    while (running()) {
        ssize_t bytes = recv(_session, buffer, 1024, 0);
        buffer[bytes] = 0;
        process_data(buffer, bytes);
    }
    close_connection();
}

void NetworkClient::process_data(char *buffer, ssize_t length) {
    ssize_t diff = 0;

    if (!_packet_length) {
        _packet_length = NetworkProtocol::packet_length(buffer);
        diff = NetworkProtocol::LENGTH_BYTES;
    }
    _buffer.push_bytes(buffer, length - diff);
    _read += length - diff;
    if (_read == _packet_length) {
        std::unique_ptr<NetworkMessage> message;
        try {
            message = std::move(NetworkProtocol::build_packet(_buffer));
            //TODO: handler.parse_packet
        } catch(std::exception &e) {
            fprintf(stderr, "client %d: %s", _session, e.what());
            //TODO: ?
        }
        //TODO: process buffer rest bytes (begin of next packet)
        _buffer.clear();
        _packet_length = 0;
        _read = 0;
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
