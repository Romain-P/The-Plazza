//
// Created by romain.pillot on 4/20/18.
//

#ifndef PLAZZA_CLIENTHANDLER_HPP
#define PLAZZA_CLIENTHANDLER_HPP

#include "AbstractPacketHandler.h"
#include "SearchRequestMessage.h"

class SlavePacketHandler: public AbstractPacketHandler {
public:
    void define_handlers(handlers_t &handlers) override;
    void searchRequested(NetworkClient *, SearchRequestMessage *msg);
private:

};

#endif //PLAZZA_SERVERHANDLER_HPP
