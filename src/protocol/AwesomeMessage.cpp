//
// Created by romain.pillot on 4/21/18.
//

#include "AwesomeMessage.h"

constexpr int32_t AwesomeMessage::PROTOCOL_ID;

void AwesomeMessage::serialize(NetworkBuffer &buffer) {
    buffer.writeUtf(_awesome);
    buffer.writeInt(_someNumber);
}

void AwesomeMessage::deserialize(NetworkBuffer &buffer) {
    _awesome = buffer.readUtf();
    _someNumber = buffer.readInt();
}

int32_t AwesomeMessage::getProtocolId() const {
    return PROTOCOL_ID;
}

std::string const &AwesomeMessage::getAwesome() const {
    return _awesome;
}

int32_t const &AwesomeMessage::getSomeNumber() const {
    return _someNumber;
}
