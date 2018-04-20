//
// Created by romain.pillot on 4/20/18.
//

#ifndef PLAZZA_PACKETPARSER_HPP
#define PLAZZA_PACKETPARSER_HPP

#include <unordered_map>
#include "NetworkClient.h"
#include "NetworkMessage.h"
#include "HelloConnectMessage.h"

class PacketHandler;
using handler_t = void (PacketHandler::*)(NetworkClient &, NetworkMessage &);

class PacketHandler {
public:
    static PacketHandler &getInstance();

    void parse_packet(NetworkClient &client, NetworkMessage &msg);
    void onHello(NetworkClient &client, HelloConnectMessage &msg);

private:
    static const std::unordered_map<int32_t, handler_t> handlers;

};

#endif //PLAZZA_PACKETPARSER_HPP
