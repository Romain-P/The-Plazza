//
// Created by romain on 18/04/2018.
//

#ifndef PLAZZA_NETWORKMESSAGE_H
#define PLAZZA_NETWORKMESSAGE_H

#include <cstdint>
#include "NetworkBuffer.h"

class NetworkMessage {
public:
    NetworkMessage(NetworkBuffer buffer) : _buffer(buffer), _id() {}
    NetworkMessage(uint32_t id) : _buffer(), _id(id){}
    virtual ~NetworkMessage();

    virtual void serialize() = 0;
    virtual void deserialize(NetworkBuffer buffer) = 0;

    uint32_t getId() const;
private:
    NetworkBuffer _buffer;
    uint32_t _id;
};

#endif //PLAZZA_NETWORKMESSAGE_H
