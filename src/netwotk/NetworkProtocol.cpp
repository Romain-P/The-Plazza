//
// Created by romain.pillot on 4/20/18.
//

#include <SearchRequestMessage.h>
#include <FreePlaceMessage.h>
#include <DestroyProcessMessage.h>
#include "SearchResultMessage.h"
#include "NetworkProtocol.h"



constexpr size_t NetworkProtocol::HEADER_INT_BYTES;

template<typename T>
std::unique_ptr<NetworkMessage> NetworkProtocol::packet_factory() {
    return std::make_unique<T>();
}

const std::unordered_map<int32_t, std::unique_ptr<NetworkMessage>(*)()> NetworkProtocol::messages {
        { SearchRequestMessage::PROTOCOL_ID, packet_factory<SearchRequestMessage> },
        { SearchResultMessage::PROTOCOL_ID, packet_factory<SearchResultMessage> },
        { FreePlaceMessage::PROTOCOL_ID, packet_factory<FreePlaceMessage> },
        { DestroyProcessMessage::PROTOCOL_ID, packet_factory<DestroyProcessMessage> }
};

int32_t NetworkProtocol::packet_length(uint8_t *buffer) {
    int32_t length;
    memcpy(&length, buffer, HEADER_INT_BYTES);
    return length;
}

std::unique_ptr<NetworkMessage> NetworkProtocol::deserialize(NetworkBuffer &buffer) {
    int32_t msg_id = buffer.readInt();
    try {
        std::unique_ptr<NetworkMessage> message(messages.at(msg_id)());
        message->deserialize(buffer);
        return message;
    } catch (std::exception &e) {
        throw std::runtime_error("can't build packet: unknown protocol id");
    }
}

void NetworkProtocol::serialize(NetworkMessage const &msg, NetworkBuffer &buffer) {
    msg.serialize(buffer);
    auto &bytes = buffer.getBytes();
    uint8_t header[HEADER_INT_BYTES * 2];

    size_t packet_length = bytes.size() + HEADER_INT_BYTES;
    int32_t protocol_id = msg.getProtocolId();

    memcpy(&header[0], &packet_length, HEADER_INT_BYTES);
    memcpy(&header[HEADER_INT_BYTES], &protocol_id, HEADER_INT_BYTES);

    bytes.insert(bytes.begin(), header, header + HEADER_INT_BYTES * 2);
}