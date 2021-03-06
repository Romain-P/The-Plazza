//
// Created by romain.pillot on 4/20/18.
//

#ifndef PLAZZA_PACKETPARSER_HPP
#define PLAZZA_PACKETPARSER_HPP

#include <unordered_map>
#include <functional>
#include <mutex>
#include <iostream>
#include "NetworkClient.h"
#include "NetworkMessage.h"

using handler_t = std::function<void (NetworkClient *, NetworkMessage *)>;
using handlers_t = std::unordered_map<int32_t, handler_t>;

template <typename T, typename V>
using typed_handler_t = void (T::*)(NetworkClient *, V *);

class AbstractPacketHandler {
public:
    virtual void init();

    /**
     * Parse a given message with a defined protocol (see @init)
     * Thread Safe.
     *
     * @param client session id of a network client
     * @param msg    received message
     */
    void parse_packet(NetworkClient *client, NetworkMessage *msg);

    virtual void define_handlers(handlers_t &handlers) = 0;

    bool ready();
    void await_ready();
protected:

    template <typename T,typename V>
    handler_t handler(T &holder, typed_handler_t<T, V> addr) {
        return [&holder, addr](NetworkClient *client, NetworkMessage *msg) mutable {
            (holder.*addr)(client, dynamic_cast<V *>(msg));
        };
    }

private:
    handlers_t _handlers;
    std::mutex _locker;
    bool _ready = false;
};

#endif //PLAZZA_PACKETPARSER_HPP
