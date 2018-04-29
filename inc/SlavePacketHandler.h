//
// Created by romain.pillot on 4/20/18.
//

#ifndef PLAZZA_CLIENTHANDLER_HPP
#define PLAZZA_CLIENTHANDLER_HPP

#include "AbstractPacketHandler.h"
#include "SearchRequestMessage.h"
#include "SlaveWorker.h"

class SlavePacketHandler: public AbstractPacketHandler {
public:
    void define_handlers(handlers_t &handlers) override;
    void searchRequested(NetworkClient *, SearchRequestMessage *msg);

    void init() override {
        if (_worker == nullptr) {
            std::cerr << "SlavePacketHandler: no slave worker found" << std::endl;
            _Exit(1);
        }
        AbstractPacketHandler::init();
    }

    void setSlaveWorker(SlaveWorker *worker) {
        _worker = worker;
    }

private:
    SlaveWorker *_worker = nullptr;
};

#endif //PLAZZA_SERVERHANDLER_HPP
