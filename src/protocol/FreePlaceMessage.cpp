//
// Created by romain on 26/04/18.
//

#include "FreePlaceMessage.h"

constexpr int32_t FreePlaceMessage::PROTOCOL_ID;

void FreePlaceMessage::serialize(NetworkBuffer &buffer) const {
    buffer.writeInt(_places);
}

void FreePlaceMessage::deserialize(NetworkBuffer &buffer) {
    _places = buffer.readInt();
}

int32_t FreePlaceMessage::getFreePlaces() const {
    return _places;
}

std::ostream &FreePlaceMessage::toString(std::ostream &o) const {
    return o << "FreePlaceMessage(places=" << std::to_string(_places) << ")";
}