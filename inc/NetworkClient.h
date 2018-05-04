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
#include "NetworkMessage.h"

class AbstractPacketHandler;

class NetworkClient {
public:
    /**
     * Create a network client listening packets received on the given socket session.
     *
     * @param session   a socket session already created
     * @param handler   packet handler for this client
     * @return          a new instance of NetworkClient
     */
    static std::unique_ptr<NetworkClient> createFromSocket(session_t session, AbstractPacketHandler &handler);


    /**
     * Create a network client listening packets received by the future socket session,
     * created by the given server port, pointing to localhost.
     *
     * @param serverPort    server port to create a socket connection pointing to localhost
     * @param handler       packet handler for this client
     * @return              a new instance of NetworkClient
     */
    static std::unique_ptr<NetworkClient> create(AbstractPacketHandler &handler, uint16_t serverPort);

    void send(NetworkMessage const &msg);
    void stop();

    bool alive() const {
        return _running;
    }

    std::thread &getThread() {
        return _thread;
    }

    void await_stop() {
        read_lock_t lock(_locker);

        if (_running) return;
        while (_session != -1);
    }

    session_t getSession() {
        read_lock_t lock(_locker);

        return _session;
    }

private:
    NetworkClient(AbstractPacketHandler *handler, uint16_t serverPort) :
            _serverPort(serverPort),
            _handler(handler),
            _session(-1),
            _thread(),
            _locker(),
            _running(true),
            _readBuffer(),
            _writeBuffer(),
            _packet_length(0),
            _read(0)
    {}

    NetworkClient(session_t session, AbstractPacketHandler *handler) :
            _serverPort(0),
            _handler(handler),
            _session(session),
            _thread(),
            _locker(),
            _running(true),
            _readBuffer(),
            _writeBuffer(),
            _packet_length(0),
            _read(0)
    {}

    uint16_t _serverPort;
    AbstractPacketHandler *_handler;
    session_t _session;
    std::thread _thread;
    std::shared_mutex _locker;
    bool _running = false;
    NetworkBuffer _readBuffer;
    NetworkBuffer _writeBuffer;
    int32_t _packet_length = 0;
    int32_t _read = 0;

    std::thread &init(bool first = true);
    void connectToServer();
    void run();
    bool running();
    void close_connection();
    void process_data(uint8_t *data, ssize_t length);
};

#endif //PLAZZA_NETWORKCLIENT_HPP
