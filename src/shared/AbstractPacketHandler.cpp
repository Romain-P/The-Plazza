//
// Created by romain.pillot on 4/20/18.
//

#include "AbstractPacketHandler.h"

void AbstractPacketHandler::parse_packet(NetworkClient *client, NetworkMessage *msg) {
    try {
        _handlers.at(msg->getProtocolId())(client, msg);
    } catch (std::exception &e) {
        throw std::runtime_error("no handler found for protocol id " + msg->getProtocolId());
    }
}

void AbstractPacketHandler::init() {
    define_handlers(_handlers);
}