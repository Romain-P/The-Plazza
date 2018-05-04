//
// Created by romain.pillot on 4/20/18.
//

#include <Logger.h>
#include <ConnectSuccessMessage.h>
#include <FreePlaceMessage.h>
#include "SlavePacketHandler.h"

using Self = SlavePacketHandler;

void Self::define_handlers(handlers_t &handlers) {
    handlers[SearchRequestMessage::PROTOCOL_ID] = handler<Self, SearchRequestMessage>(*this, &Self::searchRequested);
    handlers[DestroyProcessMessage::PROTOCOL_ID] = handler<Self, DestroyProcessMessage>(*this, &Self::onDestroy);
    handlers[ConnectSuccessMessage::PROTOCOL_ID] = handler<Self, ConnectSuccessMessage>(*this, &Self::onSuccessConnection);
}

void Self::searchRequested(NetworkClient *client, SearchRequestMessage *msg) {
    (void) client;
    _worker->search(msg->getFileNames(), msg->getRegex());
}

void Self::onDestroy(NetworkClient *client, DestroyProcessMessage *msg) {
    if (msg->force())
        _worker->stop();
    else
        _worker->workAndStop();
    client->stop();
}

void Self::onSuccessConnection(NetworkClient *client, ConnectSuccessMessage *msg) {
    (void) msg;
    client->send(FreePlaceMessage(static_cast<int32_t>(_worker->getThreadPoolSize() * 2)));
}
