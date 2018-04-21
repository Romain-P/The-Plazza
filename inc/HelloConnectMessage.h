//
// Created by romain.pillot on 4/19/18.
//

#ifndef PLAZZA_HELLOCONNECTMESSAGE_HPP
#define PLAZZA_HELLOCONNECTMESSAGE_HPP

#include "NetworkMessage.h"

class HelloConnectMessage: public NetworkMessage {

public:
    static constexpr int32_t PROTOCOL_ID = 1;

    HelloConnectMessage() : NetworkMessage(PROTOCOL_ID), _hellovar() {}

    void serialize(NetworkBuffer &buffer) override;
    void deserialize(NetworkBuffer &buffer) override;

    int32_t getHelloVar() const {
        return _hellovar;
    }

private:
    int32_t _hellovar;
};

#endif //PLAZZA_HELLOCONNECTMESSAGE_HPP
