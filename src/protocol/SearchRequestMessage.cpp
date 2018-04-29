//
// Created by romain.pillot on 4/21/18.
//

#include "SearchRequestMessage.h"

constexpr int32_t SearchRequestMessage::PROTOCOL_ID;

void SearchRequestMessage::serialize(NetworkBuffer &buffer) const {
    auto file_count = static_cast<int32_t>(_filenames.size());
    buffer.writeInt(file_count);

    for (size_t i=0; i < file_count; ++i)
        buffer.writeUtf(_filenames.at(i));
    buffer.writeUtf(_regex);
}

void SearchRequestMessage::deserialize(NetworkBuffer &buffer) {
    std::vector<std::string> file_list;

    int32_t count = buffer.readInt();

    for (size_t i=0; i < count; ++i) {
        std::string file_name = buffer.readUtf();
        file_list.push_back(file_name);
    }
    _filenames = std::vector<std::string>(file_list);
    _regex = buffer.readUtf();
}

std::vector<std::string> const &SearchRequestMessage::getFileNames() const {
    return _filenames;
}

std::string const &SearchRequestMessage::getRegex() const {
    return _regex;
}

std::ostream &SearchRequestMessage::toString(std::ostream &o) const {
    std::string files;
    size_t count = _filenames.size();

    for (size_t i=0; i < count; ++i) {
        if (!i || i == count - 1)
            files += ',';
        files += " " + _filenames.at(i);
    }
    return o << "SearchRequestMessage("
             << "files={" << files << " }, "
             << "regex='" << _regex << "')";
}