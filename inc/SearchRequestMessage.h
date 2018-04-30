//
// Created by romain.pillot on 4/21/18.
//

#ifndef PLAZZA_SEARCHREQUESTMESSAGE_H
#define PLAZZA_SEARCHREQUESTMESSAGE_H

#include <utility>
#include "NetworkMessage.h"

class SearchRequestMessage : public NetworkMessage {

public:
    static constexpr int32_t PROTOCOL_ID = 1;

    SearchRequestMessage(std::vector<std::string> &filenames, std::string const &regex) : NetworkMessage(PROTOCOL_ID),
                                                         _filenames(filenames),
                                                         _regex(regex)
    {}

    SearchRequestMessage() : NetworkMessage(PROTOCOL_ID), _filenames(), _regex() {}

    void serialize(NetworkBuffer &buffer) const override;
    void deserialize(NetworkBuffer &buffer) override;

    std::vector<std::string> &getFileNames();
    std::string const &getRegex() const;

    std::ostream &toString(std::ostream &o) const override;

private:
    std::vector<std::string> _filenames;
    std::string _regex;
};

#endif //PLAZZA_SEARCHREQUESTMESSAGE_H
