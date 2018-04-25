//
// Created by romain.pillot on 4/19/18.
//

#include "HelloConnectMessage.h"

int32_t constexpr HelloConnectMessage::PROTOCOL_ID;

void HelloConnectMessage::serialize(NetworkBuffer &buffer) const {
    buffer.writeInt(_hellovar);
}

void HelloConnectMessage::deserialize(NetworkBuffer &buffer) {
    _hellovar = buffer.readInt();
}