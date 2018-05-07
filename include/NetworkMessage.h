//
// Created by romain on 18/04/2018.
//

#ifndef PLAZZA_NETWORKMESSAGE_H
#define PLAZZA_NETWORKMESSAGE_H

#include <cstdint>
#include <iostream>
#include "NetworkBuffer.h"

class NetworkMessage {
public:
    virtual ~NetworkMessage() = default;
    explicit NetworkMessage(int32_t protocol_id) : _protocolId(protocol_id) {};

    virtual void serialize(NetworkBuffer &buffer) const = 0;
    virtual void deserialize(NetworkBuffer &buffer) = 0;

    virtual std::ostream& toString(std::ostream& o) const {
        return o << "NetworkMessage(id=" << _protocolId << ")";
    }

    int32_t getProtocolId() const {
        return _protocolId;
    }

private:
    int32_t _protocolId;
};

inline std::ostream &operator<<(std::ostream &o, const NetworkMessage &msg) {
    return msg.toString(o);
}

#endif //PLAZZA_NETWORKMESSAGE_H
