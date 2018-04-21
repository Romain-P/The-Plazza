//
// Created by romain.pillot on 4/20/18.
//

#include "SlavePacketHandler.h"


void ClientHandler::define_handlers(handlers_t &handlers) {
    handlers[AwesomeMessage::PROTOCOL_ID] = handler<ClientHandler, AwesomeMessage>(*this, &ClientHandler::onAwesome);
}

void ClientHandler::onAwesome(NetworkClient *client, AwesomeMessage *msg) {
    printf("deserialized awesome: %s %d\n", msg->getAwesome(), msg->getSomeNumber());
}