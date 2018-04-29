//
// Created by romain.pillot on 4/19/18.
//

#include <NetworkProtocol.h>
#include <AbstractPacketHandler.h>
#include "NetworkClient.h"
#include "Logger.h"
#include <poll.h>

std::unique_ptr<NetworkClient> NetworkClient::createFromSocket(session_t session, AbstractPacketHandler &handler) {
    auto client = std::unique_ptr<NetworkClient>(new NetworkClient(session, &handler));
    client->init();
    return client;
}

std::unique_ptr<NetworkClient> NetworkClient::create(AbstractPacketHandler &handler, uint16_t serverPort) {
    auto client = std::unique_ptr<NetworkClient>(new NetworkClient(&handler, serverPort));
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

    connectToServer();

    pollfd_t params = {_session, POLLIN, 0};
    while (running()) {
#if defined (WIN32)
        if (WSAPoll(&params, 1, 10) <= 0)
#elif defined linux
        if (poll(&params, 1, 10) <= 0)
#endif
            continue;
        ssize_t bytes = recv(_session, buffer, 1024, 0);
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
        diff = NetworkProtocol::HEADER_INT_BYTES;
        buffer += NetworkProtocol::HEADER_INT_BYTES;
    }
    bool next_began = _read + length - diff > _packet_length;
    if (next_began)
        diff += (next_length = _read + length - diff - _packet_length);
    next_begin = length - diff;
    _readBuffer.push_bytes(buffer, next_begin);
    _read += next_begin;
    if (_read == _packet_length) {
        std::unique_ptr<NetworkMessage> message;
        try {
            message = std::move(NetworkProtocol::deserialize(_readBuffer));
            Logger::log("Recv: ", *message);
            _handler->parse_packet(this, message.get());
        } catch(std::exception &e) {
            fprintf(stderr, "client %d: %s", _session, e.what());
        }
        _readBuffer.clear();
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
    _session = -1;
}

//connect to the server if the socket is not created yet
void NetworkClient::connectToServer() {
    if (_session != -1)
        goto running;

    if ((_session = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
        goto error;

    insocket_t server;
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server.sin_family = AF_INET;
    server.sin_port = htons(_serverPort);

    if (connect(_session, reinterpret_cast<socket_t *>(&server), sizeof(server)) == SOCKET_ERROR) {
        error:
        perror("NetworkClient: can't connect to server");
        exit(1);
    }

    running:
    _locker.lock();
    _running = true;
    _locker.unlock();
}

void NetworkClient::send(NetworkMessage const &msg) {
    write_lock_t lock(_locker);

    while (!_running);
    _writeBuffer.clear();
    NetworkProtocol::serialize(msg, _writeBuffer);
    auto &buffer = _writeBuffer.getBytes();
    Logger::log("Sent: ", msg);
    ::send(_session, &buffer[0], buffer.size(), 0);
}
