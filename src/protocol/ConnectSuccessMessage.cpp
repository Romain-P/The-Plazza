//
// Created by romain on 04/05/18.
//

#include "ConnectSuccessMessage.h"

constexpr int32_t ConnectSuccessMessage::PROTOCOL_ID;

void ConnectSuccessMessage::serialize(NetworkBuffer &buffer) const {
    (void) buffer;
}

void ConnectSuccessMessage::deserialize(NetworkBuffer &buffer) {
    (void) buffer;
}

std::ostream &ConnectSuccessMessage::toString(std::ostream &o) const {
    return o << "ConnectSuccessMessage()";
}
