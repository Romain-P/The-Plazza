//
// Created by romain on 26/04/18.
//

#ifndef PLAZZA_STATEREQUESTMESSAGE_H
#define PLAZZA_STATEREQUESTMESSAGE_H


#include "NetworkMessage.h"

class FreePlaceMessage : public NetworkMessage {

public:
    static constexpr int32_t PROTOCOL_ID = 3;

    FreePlaceMessage(int32_t places) : NetworkMessage(PROTOCOL_ID),
                                         _places(places) {};

    FreePlaceMessage() : NetworkMessage(PROTOCOL_ID), _places() {}

    void serialize(NetworkBuffer &buffer) const override;
    void deserialize(NetworkBuffer &buffer) override;

    int32_t getFreePlaces() const;

    std::ostream &toString(std::ostream &o) const override;

private:
    int32_t _places;
};


#endif //PLAZZA_STATEREQUESTMESSAGE_H