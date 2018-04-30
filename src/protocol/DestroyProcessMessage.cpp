//
// Created by romain on 30/04/18.
//

#include "DestroyProcessMessage.h"

constexpr int32_t DestroyProcessMessage::PROTOCOL_ID;

void DestroyProcessMessage::serialize(NetworkBuffer &buffer) const {
}

void DestroyProcessMessage::deserialize(NetworkBuffer &buffer) {
}

std::ostream &DestroyProcessMessage::toString(std::ostream &o) const {
    return o << "DestroyProcessMessage()";
}