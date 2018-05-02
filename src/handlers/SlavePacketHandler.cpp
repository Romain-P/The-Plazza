//
// Created by romain.pillot on 4/20/18.
//

#include <Logger.h>
#include "SlavePacketHandler.h"

using Self = SlavePacketHandler;

void Self::define_handlers(handlers_t &handlers) {
    handlers[SearchRequestMessage::PROTOCOL_ID] = handler<Self, SearchRequestMessage>(*this, &Self::searchRequested);
    handlers[DestroyProcessMessage::PROTOCOL_ID] = handler<Self, DestroyProcessMessage>(*this, &Self::onDestroy);
}

void Self::searchRequested(NetworkClient *client, SearchRequestMessage *msg) {
    _worker->search(msg->getFileNames(), msg->getRegex());
}

void Self::onDestroy(NetworkClient *client, DestroyProcessMessage *msg) {
    if (msg->force())
        _worker->stop();
    else
        _worker->workAndStop();
    client->stop();
}