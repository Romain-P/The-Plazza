//
// Created by romain on 30/04/18.
//

#ifndef PLAZZA_DESTROYPROCESSMESSAGE_H
#define PLAZZA_DESTROYPROCESSMESSAGE_H


#include "NetworkMessage.h"

class DestroyProcessMessage : public NetworkMessage {

public:
    static constexpr int32_t PROTOCOL_ID = 4;

    DestroyProcessMessage() : NetworkMessage(PROTOCOL_ID) {}

    void serialize(NetworkBuffer &buffer) const override;
    void deserialize(NetworkBuffer &buffer) override;


    std::ostream &toString(std::ostream &o) const override;
};


#endif //PLAZZA_DESTROYPROCESSMESSAGE_H
