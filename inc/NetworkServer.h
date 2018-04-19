//
// Created by romain on 18/04/2018.
//

#ifndef PLAZZA_NETWORKSERVER_H
# define PLAZZA_NETWORKSERVER_H

#include <thread>
#include <mutex>
# include "Shared.h"

# define RANDOM_PORT    0

class NetworkServer {

public:
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

private:
    std::thread _thread;
    insocket_t _server;
    session_t _session = -1;
    std::mutex _locker;
    bool _stopRequested = false;

    void configure();
    void await_clients();
    void error(std::string err) const;
    void close_all();
    bool stop_requested();
};

#endif //PLAZZA_NETWORKSERVER_H
