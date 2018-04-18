//
// Created by romain on 18/04/2018.
//

#include "NetworkServer.h"

std::thread &NetworkServer::init(bool first) {
    if (first) {
        _thread = std::thread(&NetworkServer::init, this, false);
    } else {
        configure();
        await_clients(); /** blocking until stop requested **/
    }
    return _thread;
}

void NetworkServer::close_all() {
    close_socket(_session);
    #if defined (WIN32)
        WSACleanup();
    #endif
}

void NetworkServer::await_clients() {
    session_t client_session;
    insocket_t client_insocket;
    socklen_t clientsocksize = sizeof(client_insocket);

    printf("blocking test\n");
    while ((client_session = accept(_session, reinterpret_cast<socket_t *>(&client_insocket), &clientsocksize)) != SOCKET_ERROR) {
        printf("TODO clients holding, data serialization");
    }
    printf("appears when ::close_all() \n");
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
}

void NetworkServer::error(std::string const err) const {
    perror(err.c_str());
    exit(1);
}
