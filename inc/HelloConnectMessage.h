//
// Created by romain.pillot on 4/19/18.
//

#ifndef PLAZZA_HELLOCONNECTMESSAGE_HPP
#define PLAZZA_HELLOCONNECTMESSAGE_HPP

#include "NetworkMessage.h"

class HelloConnectMessage: public NetworkMessage {

public:
    static constexpr int32_t PROTOCOL_ID = 1;

    void serialize(NetworkBuffer &buffer) override;
    void deserialize(NetworkBuffer &buffer) override;
    int32_t getProtocolId() const override;

    int32_t getHelloVar() const;
private:
    int32_t _hellovar;
};

#endif //PLAZZA_HELLOCONNECTMESSAGE_HPP
