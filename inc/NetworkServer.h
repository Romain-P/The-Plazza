//
// Created by romain on 18/04/2018.
//

#ifndef PLAZZA_NETWORKSERVER_H
# define PLAZZA_NETWORKSERVER_H

#include <thread>
#include <mutex>
#include <unordered_map>
# include "Shared.h"
#include "NetworkClient.h"
#include "AbstractPacketHandler.h"

# define RANDOM_PORT    0

class NetworkServer {

public:

    explicit NetworkServer(AbstractPacketHandler *clientHandler) :
        _clientHandler(clientHandler),
        _thread(),
        _server(),
        _session(-1),
        _locker(),
        _clients(),
        _stopRequested(false),
        _port(0)
    {}

    /**
     * Initialize the network server unto a new thread, on a random available port of the machine.
     * Do not pass argument to this function!
     *
     * @param first     useful to know when the function is called by itself
     * @return          the created thread that has to be joined on the upper scope
     */
    std::thread &init(bool first = true);

    /**
     * Closes all connections and then the server socket.
     */
    void stop();

    /**
     * @return  the generated port by the server
     */
    uint16_t const &getPort() const {
        read_lock_t (_locker);
        while (!_port);
        return _port;
    }

private:
    AbstractPacketHandler *_clientHandler;
    std::thread _thread;
    insocket_t _server;
    session_t _session = -1;
    std::shared_mutex _locker;
    std::unordered_map<session_t, std::unique_ptr<NetworkClient>> _clients;
    bool _stopRequested;
    uint16_t _port;


    void configure();
    void await_clients();
    void error(std::string err) const;
    void close_all();
    bool stop_requested();
    void retrieve_port();
};

#endif //PLAZZA_NETWORKSERVER_H
