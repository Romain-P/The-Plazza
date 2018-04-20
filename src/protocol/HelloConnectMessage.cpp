//
// Created by romain.pillot on 4/19/18.
//

#include "HelloConnectMessage.h"

int32_t constexpr HelloConnectMessage::PROTOCOL_ID;

void HelloConnectMessage::serialize(NetworkBuffer &buffer) {
    buffer.writeInt(_hellovar);
}

void HelloConnectMessage::deserialize(NetworkBuffer &buffer) {
    _hellovar = buffer.readInt();
}

int32_t HelloConnectMessage::getProtocolId() const {
    return PROTOCOL_ID;
}

int32_t HelloConnectMessage::getHelloVar() const {
    return _hellovar;
}
