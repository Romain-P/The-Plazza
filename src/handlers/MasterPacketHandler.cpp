//
// Created by romain.pillot on 4/20/18.
//

#include <SearchRequestMessage.h>
#include <DestroyProcessMessage.h>
#include "MasterPacketHandler.h"
#include "FreePlaceMessage.h"

using Self = MasterPacketHandler;

void Self::define_handlers(handlers_t &handlers) {
    handlers[SearchResultMessage::PROTOCOL_ID] = handler(*this, &Self::onSearchResult);
    handlers[FreePlaceMessage::PROTOCOL_ID] = handler(*this, &Self::onFreePlace);
    handlers[DestroyProcessMessage::PROTOCOL_ID] = handler(*this, &Self::onSlaveTimeout);
}

void Self::onSearchResult(NetworkClient *client, SearchResultMessage *msg) {
    (void) client;
    std::cout << msg->getResult() << std::endl;
    //TODO: logger msg->getRegex() + result
}

void Self::onFreePlace(NetworkClient *client, FreePlaceMessage *msg) {
    _dispatcher->refresh_free_places(client->getSession(), msg->getFreePlaces());
}

void Self::onSlaveTimeout(NetworkClient *client, DestroyProcessMessage *msg) {
    (void) msg;
    _dispatcher->slave_timedout(client);
}