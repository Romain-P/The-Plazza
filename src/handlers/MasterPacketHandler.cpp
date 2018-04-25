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
    printf("deserialized hellomsg: %d\n", msg->getHelloVar());
    client->send(AwesomeMessage("this is awesome", 10)); //sending awesome to slave client
}

void Self::onAwesomeMsg(NetworkClient *client, AwesomeMessage *msg) {
    printf("deserialized awesome: %s %d\n", msg->getAwesome(), msg->getSomeNumber());
}