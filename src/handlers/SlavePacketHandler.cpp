//
// Created by romain.pillot on 4/20/18.
//

#include "SlavePacketHandler.h"

using Self = SlavePacketHandler;

void Self::define_handlers(handlers_t &handlers) {
    handlers[SearchRequestMessage::PROTOCOL_ID] = handler<Self, SearchRequestMessage>(*this, &Self::searchRequested);
}

void Self::searchRequested(NetworkClient *client, SearchRequestMessage *msg) {
    //TODO
}