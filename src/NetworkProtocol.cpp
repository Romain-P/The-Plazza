//
// Created by romain on 18/04/2018.
//

#include "../inc/NetworkProtocol.h"
#include "../inc/NetworkMessage.h"

uint32_t NetworkMessage::getId() const {
    return _id;
}