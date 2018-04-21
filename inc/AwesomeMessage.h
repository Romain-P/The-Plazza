//
// Created by romain.pillot on 4/21/18.
//

#ifndef PLAZZA_AWESOMEMESSAGE_H
#define PLAZZA_AWESOMEMESSAGE_H

#include "NetworkMessage.h"

class AwesomeMessage: public NetworkMessage {

public:
    static constexpr int32_t PROTOCOL_ID = 2;

    void serialize(NetworkBuffer &buffer) override;
    void deserialize(NetworkBuffer &buffer) override;
    int32_t getProtocolId() const override;

    std::string const &getAwesome() const;
    int32_t const &getSomeNumber() const;
private:
    std::string _awesome;
    int32_t _someNumber;
};

#endif //PLAZZA_AWESOMEMESSAGE_H
