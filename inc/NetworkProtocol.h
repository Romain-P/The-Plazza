//
// Created by romain on 18/04/2018.
//

#ifndef PROJECT_NETWORKPROTOCOL_H
#define PROJECT_NETWORKPROTOCOL_H

#include <cstdint>
#include <cstring>
#include <unordered_map>
#include <stdexcept>
#include <memory>
#include "NetworkMessage.h"
#include "HelloConnectMessage.h"

class NetworkProtocol {
public:

    static constexpr size_t LENGTH_BYTES = sizeof(int32_t);

    template<typename T>
    static std::unique_ptr<NetworkMessage> packet_factory();

    static int32_t packet_length(uint8_t *buffer);
    static std::unique_ptr<NetworkMessage> build_packet(NetworkBuffer &buffer);
private:
    static const std::unordered_map<int32_t, std::unique_ptr<NetworkMessage>(*)()> messages;
};

#endif //PROJECT_NETWORKPROTOCOL_H
