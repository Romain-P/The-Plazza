//
// Created by romain.pillot on 4/21/18.
//

#ifndef PLAZZA_SEARCHRESULTMESSAGE_H
#define PLAZZA_SEARCHRESULTMESSAGE_H

#include "NetworkMessage.h"

class SearchResultMessage : public NetworkMessage {

public:
    static constexpr int32_t PROTOCOL_ID = 2;

    SearchResultMessage(std::string &result, std::string &pattern) : NetworkMessage(PROTOCOL_ID),
                                                         _result(result), _pattern(pattern){}

    SearchResultMessage() : NetworkMessage(PROTOCOL_ID), _result(){}

    void serialize(NetworkBuffer &buffer) const override;
    void deserialize(NetworkBuffer &buffer) override;

    std::string const &getResult() const;
    std::string const &getPattern() const;

    std::ostream &toString(std::ostream &o) const override;

private:
    std::string _result;
    std::string _pattern;
};

#endif //PLAZZA_SEARCHRESULTMESSAGE_H
