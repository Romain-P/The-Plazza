//
// Created by romain.pillot on 4/20/18.
//

#include <AwesomeMessage.h>
#include "NetworkProtocol.h"



constexpr size_t NetworkProtocol::LENGTH_BYTES;

template<typename T>
std::unique_ptr<NetworkMessage> NetworkProtocol::packet_factory() {
    return std::make_unique<T>();
}

const std::unordered_map<int32_t, std::unique_ptr<NetworkMessage>(*)()> NetworkProtocol::messages {
        { HelloConnectMessage::PROTOCOL_ID, packet_factory<HelloConnectMessage> },
        { AwesomeMessage::PROTOCOL_ID, packet_factory<AwesomeMessage> }
};

int32_t NetworkProtocol::packet_length(char *buffer) {
    int32_t length;
    memcpy(&length, buffer, LENGTH_BYTES);
}

std::unique_ptr<NetworkMessage> NetworkProtocol::build_packet(NetworkBuffer &buffer) {
    int32_t msg_id = buffer.readInt();
    try {
        return messages.at(msg_id)();
    } catch (std::exception &e) {
        throw std::runtime_error("can't build packet: unknown protocol id");
    }
}