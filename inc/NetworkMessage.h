//
// Created by romain on 18/04/2018.
//

#ifndef PLAZZA_NETWORKMESSAGE_H
#define PLAZZA_NETWORKMESSAGE_H

#include <cstdint>
#include "NetworkBuffer.h"

class NetworkMessage {
public:
    virtual ~NetworkMessage() = default;
    explicit NetworkMessage(int32_t protocol_id) : _protocolId(protocol_id) {};

    virtual void serialize(NetworkBuffer &buffer) = 0;
    virtual void deserialize(NetworkBuffer &buffer) = 0;

    int32_t getProtocolId() {
        return _protocolId;
    }

private:
    int32_t _protocolId;
};

#endif //PLAZZA_NETWORKMESSAGE_H
