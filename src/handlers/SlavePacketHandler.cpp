//
// Created by romain.pillot on 4/20/18.
//

#include <HelloConnectMessage.h>
#include "SlavePacketHandler.h"

using Self = SlavePacketHandler;

void Self::define_handlers(handlers_t &handlers) {
    handlers[AwesomeMessage::PROTOCOL_ID] = handler<Self, AwesomeMessage>(*this, &Self::onAwesome);
}

void Self::onAwesome(NetworkClient *client, AwesomeMessage *msg) {
    printf("deserialized awesome: %s %d\n", msg->getAwesome(), msg->getSomeNumber());
    client->send(HelloConnectMessage());
}