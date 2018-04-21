//
// Created by romain.pillot on 4/20/18.
//

#include "SlavePacketHandler.h"


void SlavePacketHandler::define_handlers(handlers_t &handlers) {
    handlers[AwesomeMessage::PROTOCOL_ID] = handler<SlavePacketHandler, AwesomeMessage>(*this, &SlavePacketHandler::onAwesome);
}

void SlavePacketHandler::onAwesome(NetworkClient *client, AwesomeMessage *msg) {
    printf("deserialized awesome: %s %d\n", msg->getAwesome(), msg->getSomeNumber());
}