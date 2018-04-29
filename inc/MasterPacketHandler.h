//
// Created by romain.pillot on 4/20/18.
//

#ifndef PLAZZA_SERVERHANDLER_HPP
#define PLAZZA_SERVERHANDLER_HPP

#include "AbstractPacketHandler.h"
#include "SearchResultMessage.h"
#include "FreePlaceMessage.h"
#include "TaskDispatcher.h"

class MasterPacketHandler: public AbstractPacketHandler {
public:
    void define_handlers(handlers_t &handlers) override;

    void onSearchResult(NetworkClient *client, SearchResultMessage *msg);
    void onFreePlace(NetworkClient *client, FreePlaceMessage *msg);

    void init() override {
        if (_dispatcher == nullptr) {
            std::cerr << "MasterPacketHandler: no task dispatcher found" << std::endl;
            exit(1);
        }

        AbstractPacketHandler::init();
    }

    void setTaskDispatcher(TaskDispatcher *dispatcher) {
        _dispatcher = dispatcher;
    }

private:
    TaskDispatcher *_dispatcher = nullptr;
};

#endif //PLAZZA_SERVERHANDLER_HPP
