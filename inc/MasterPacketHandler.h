//
// Created by romain.pillot on 4/20/18.
//

#ifndef PLAZZA_SERVERHANDLER_HPP
#define PLAZZA_SERVERHANDLER_HPP

#include "AbstractPacketHandler.h"
#include "HelloConnectMessage.h"
#include "AwesomeMessage.h"

class ServerHandler: public AbstractPacketHandler {
public:
    void define_handlers(handlers_t &handlers) override;

    void onHello(NetworkClient *, HelloConnectMessage *msg);
    void onAwesomeMsg(NetworkClient *client, AwesomeMessage *msg);
private:

};

#endif //PLAZZA_SERVERHANDLER_HPP
