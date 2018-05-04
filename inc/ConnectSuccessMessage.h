//
// Created by romain on 04/05/18.
//

#ifndef PLAZZA_CONNECTSUCCESSMESSAGE_H
#define PLAZZA_CONNECTSUCCESSMESSAGE_H


#include <NetworkMessage.h>

class ConnectSuccessMessage : public NetworkMessage {

public:
    static constexpr int32_t PROTOCOL_ID = 5;

    ConnectSuccessMessage() : NetworkMessage(PROTOCOL_ID) {}

    void serialize(NetworkBuffer &buffer) const override;
    void deserialize(NetworkBuffer &buffer) override;

    std::ostream &toString(std::ostream &o) const override;
};


#endif //PLAZZA_CONNECTSUCCESSMESSAGE_H
