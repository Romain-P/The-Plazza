//
// Created by romain.pillot on 4/20/18.
//

#include "PacketHandler.h"

const std::unordered_map<int32_t, handler_t> PacketHandler::handlers {
        { HelloConnectMessage::PROTOCOL_ID, reinterpret_cast<handler_t>(&PacketHandler::onHello) }
};

void PacketHandler::onHello(NetworkClient &client, HelloConnectMessage &msg) {
    printf("hello var %d\n", msg.getHelloVar());
}

void PacketHandler::parse_packet(NetworkClient &client, NetworkMessage &msg) {
    try {
        (this->*handlers.at(msg.getProtocolId()))(client, msg);
    } catch (std::exception &e) {
        throw std::runtime_error("no handler found for protocol id " + msg.getProtocolId());
    }
}

PacketHandler &PacketHandler::getInstance() {
    static PacketHandler handler;
    return handler;
}
