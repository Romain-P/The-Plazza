//
// Created by romain.pillot on 4/21/18.
//

#ifndef PLAZZA_AWESOMEMESSAGE_H
#define PLAZZA_AWESOMEMESSAGE_H

#include <utility>
#include "NetworkMessage.h"

class AwesomeMessage: public NetworkMessage {

public:
    static constexpr int32_t PROTOCOL_ID = 2;

    AwesomeMessage(std::string _awesome, int32_t some) : NetworkMessage(PROTOCOL_ID),
                                                         _awesome(_awesome),
                                                         _someNumber(some) {}

    AwesomeMessage() : NetworkMessage(PROTOCOL_ID), _awesome(), _someNumber() {}

    void serialize(NetworkBuffer &buffer) const override;
    void deserialize(NetworkBuffer &buffer) override;

    std::string const &getAwesome() const {
        return _awesome;
    }
    int32_t const &getSomeNumber() const {
        return _someNumber;
    }

private:
    std::string _awesome;
    int32_t _someNumber;
};

#endif //PLAZZA_AWESOMEMESSAGE_H
