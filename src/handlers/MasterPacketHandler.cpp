//
// Created by romain.pillot on 4/20/18.
//

#include "AwesomeMessage.h"
#include "MasterPacketHandler.h"


void ServerHandler::define_handlers(handlers_t &handlers) {
    handlers[HelloConnectMessage::PROTOCOL_ID] = handler<ServerHandler, HelloConnectMessage>(*this, &ServerHandler::onHello);
    handlers[AwesomeMessage::PROTOCOL_ID] = handler<ServerHandler, AwesomeMessage>(*this, &ServerHandler::onAwesomeMsg);
}

void ServerHandler::onHello(NetworkClient *client, HelloConnectMessage *msg) {
    printf("deserialized hellomsg: %d\n", msg->getHelloVar());
}

void ServerHandler::onAwesomeMsg(NetworkClient *client, AwesomeMessage *msg) {
    printf("deserialized awesome: %s %d\n", msg->getAwesome(), msg->getSomeNumber());
}