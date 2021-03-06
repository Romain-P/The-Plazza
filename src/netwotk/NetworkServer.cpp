//
// Created by romain on 18/04/2018.
//

#include <fcntl.h>
#include <csignal>
#include "NetworkServer.h"
#include <poll.h>
#include <iostream>
#include "SearchRequestMessage.h"
#include "DestroyProcessMessage.h"
#include <sys/wait.h>
#include <ConnectSuccessMessage.h>

std::thread &NetworkServer::init(bool first) {
    if (first) {
        _thread = std::thread(&NetworkServer::init, this, false);
    } else {
        configure();
        await_clients(); /** blocking until stop requested **/
    }
    return _thread;
}

void NetworkServer::await_clients() {
    session_t client_session;
    insocket_t client_insocket;
    socklen_t clientsocksize = sizeof(client_insocket);

    pollfd_t params = {_session, POLLIN, 0};
    while (!stop_requested()) {
#if defined (WIN32)
        if (WSAPoll(&params, 1, 10) <= 0)
#elif defined linux
        if (poll(&params, 1, 10) <= 0)
#endif
            continue;
        client_session = accept(_session, reinterpret_cast<socket_t *>(&client_insocket), &clientsocksize);

        if (client_session == SOCKET_ERROR) {
            std::cerr << "Socket accept error" << std::endl;
            break;
        }

        _clients[client_session] = std::move(NetworkClient::createFromSocket(client_session, *_clientHandler));
        _clients[client_session]->send(ConnectSuccessMessage());

    }
    close_all();
}

/**
 * Configure the server socket,
 * Bind on localhost to a random available port
 */
void NetworkServer::configure() {
#if defined (WIN32)
    WSADATA WSAData;
    int startup_error = WSAStartup(MAKEWORD(2,2), &WSAData);
#else
    int startup_error = 0;
#endif

    if (startup_error)
        error("Error found while trying to setup windows sockets.");
    else if ((_session = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
        error("Cant init the server socket\n");

    _server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    _server.sin_family = AF_INET;
    _server.sin_port = htons(RANDOM_PORT);

    if (bind(_session, (socket_t *) &_server, sizeof(_server)) == SOCKET_ERROR)
        error("Cannot bind the server socket");
    else if (listen(_session, SOMAXCONN) == SOCKET_ERROR)
        error("Cannot listen client sockets");

    retrieve_port();
    _ready = true;
}

void NetworkServer::error(std::string const err) const {
    perror(err.c_str());
    exit(1);
}

void NetworkServer::stop() {
    write_lock_t lock(_locker);

    _stopRequested = true;
}

void NetworkServer::close_all() {
    write_lock_t lock(_locker);

    if (_session == -1)
        return;
    for (auto &keyset: _clients) {
        NetworkClient *client = keyset.second.get();
        client->send(DestroyProcessMessage());
        client->stop();
        client->await_stop();
        client->getThread().join();
    }
    _clients.clear();
    _session = -1;
    close_socket(_session);
#if defined (WIN32)
    WSACleanup();
#endif
}

bool NetworkServer::stop_requested() {
    read_lock_t lock(_locker);

    return _stopRequested;
}

void NetworkServer::retrieve_port() {
    socklen_t addrlen = sizeof(_server);
    if(getsockname(_session, reinterpret_cast<socket_t *>(&_server), &addrlen) == 0 &&
       _server.sin_family == AF_INET && addrlen == sizeof(_server))  {
        _port = static_cast<uint16_t >(ntohs(_server.sin_port));
    }
    else
        error("retrieve_port");
}
