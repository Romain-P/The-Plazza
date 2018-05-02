//
// Created by romain on 30/04/18.
//

#include "DestroyProcessMessage.h"

constexpr int32_t DestroyProcessMessage::PROTOCOL_ID;

void DestroyProcessMessage::serialize(NetworkBuffer &buffer) const {
    buffer.writeBool(_force);
}

void DestroyProcessMessage::deserialize(NetworkBuffer &buffer) {
    _force = buffer.readBool();
}

std::ostream &DestroyProcessMessage::toString(std::ostream &o) const {
    return o << "DestroyProcessMessage(force=" << (_force ? "true" : "false") << ")";
}

bool DestroyProcessMessage::force() const {
    return _force;
}
