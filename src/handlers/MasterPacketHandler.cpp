//
// Created by romain.pillot on 4/20/18.
//

#include "AwesomeMessage.h"
#include "MasterPacketHandler.h"


void MasterPacketHandler::define_handlers(handlers_t &handlers) {
    handlers[HelloConnectMessage::PROTOCOL_ID] = handler<MasterPacketHandler, HelloConnectMessage>(*this, &MasterPacketHandler::onHello);
    handlers[AwesomeMessage::PROTOCOL_ID] = handler<MasterPacketHandler, AwesomeMessage>(*this, &MasterPacketHandler::onAwesomeMsg);
}

void MasterPacketHandler::onHello(NetworkClient *client, HelloConnectMessage *msg) {
    printf("deserialized hellomsg: %d\n", msg->getHelloVar());
}

void MasterPacketHandler::onAwesomeMsg(NetworkClient *client, AwesomeMessage *msg) {
    printf("deserialized awesome: %s %d\n", msg->getAwesome(), msg->getSomeNumber());
}