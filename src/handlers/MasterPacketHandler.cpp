//
// Created by romain.pillot on 4/20/18.
//

#include "AwesomeMessage.h"
#include "MasterPacketHandler.h"

using Self = MasterPacketHandler;

void Self::define_handlers(handlers_t &handlers) {
    handlers[HelloConnectMessage::PROTOCOL_ID] = handler<Self, HelloConnectMessage>(*this, &Self::onHello);
    handlers[AwesomeMessage::PROTOCOL_ID] = handler<Self, AwesomeMessage>(*this, &Self::onAwesomeMsg);
}

void Self::onHello(NetworkClient *client, HelloConnectMessage *msg) {
}

void Self::onAwesomeMsg(NetworkClient *client, AwesomeMessage *msg) {
}