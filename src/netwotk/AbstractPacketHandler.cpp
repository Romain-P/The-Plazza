//
// Created by romain.pillot on 4/20/18.
//

#include "AbstractPacketHandler.h"

void AbstractPacketHandler::parse_packet(NetworkClient *client, NetworkMessage *msg) {
    lock_t lock(_locker);
    try {
        _handlers.at(msg->getProtocolId())(client, msg);
    } catch (std::exception &e) {
        std::cerr << "no handler found for protocol id " << msg->getProtocolId() << std::endl;
        throw std::runtime_error(e.what());
    }
}

void AbstractPacketHandler::init() {
    define_handlers(_handlers);
    _ready = true;
}

bool AbstractPacketHandler::ready() {
    return _ready;
}

void AbstractPacketHandler::await_ready() {
    while (!ready());
}
