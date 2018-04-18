//
// Created by romain on 18/04/2018.
//

#ifndef PLAZZA_NETWORKMESSAGE_H
#define PLAZZA_NETWORKMESSAGE_H

#include <cstdint>
#include "NetworkBuffer.h"

class NetworkMessage {
public:
    virtual ~NetworkMessage();

    virtual void serialize(NetworkBuffer buffer) = 0;
    virtual void deserialize(NetworkBuffer buffer) = 0;

    virtual uint32_t getProtocolId() const = 0;
};

#endif //PLAZZA_NETWORKMESSAGE_H
