//
// Created by romain on 18/04/2018.
//

#include "../inc/NetworkBuffer.h"
#include <cstring>

template<typename T>
void NetworkBuffer::readBytes(T &to_fill) {
    size_t size = sizeof(T);
    memcpy(&to_fill, &_buffer[_pos], size);
    _pos += size;
}

template<typename T>
void NetworkBuffer::writeBytes(T &to_copy) {
    size_t size = sizeof(T);
    if (_pos + size > _buffer.size())
        _buffer.resize(_pos + size);
    memcpy(&_buffer[_pos], reinterpret_cast<char *>(&to_copy), size);
    _pos += size;
}

int32_t NetworkBuffer::readInt() {
    int32_t value;
    readBytes(value);
    return value;
}

void NetworkBuffer::writeInt(int32_t value) {
    writeBytes(value);
}

std::string NetworkBuffer::readUtf() {
    std::string value;
    //TODO
    return value;
}

void NetworkBuffer::writeUtf(std::string value) {
    auto length = static_cast<int32_t>(value.length());
    writeBytes(length);
    //TODO: write the string
}