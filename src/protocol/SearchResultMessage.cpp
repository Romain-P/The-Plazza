//
// Created by romain on 26/04/18.
//

#include "SearchResultMessage.h"

constexpr int32_t SearchResultMessage::PROTOCOL_ID;

void SearchResultMessage::serialize(NetworkBuffer &buffer) const {
    buffer.writeUtf(_result);
    buffer.writeUtf(_pattern);
}

void SearchResultMessage::deserialize(NetworkBuffer &buffer) {
    _result = buffer.readUtf();
    _pattern = buffer.readUtf();
}

std::string const &SearchResultMessage::getResult() const {
    return _result;
}

std::string const &SearchResultMessage::getPattern() const {
    return _pattern;
}


std::ostream &SearchResultMessage::toString(std::ostream &o) const {
    return o << "SearchResultMessage("
             << "result='" << _result << "', "
             << "pattern='" << _pattern << "')";
}