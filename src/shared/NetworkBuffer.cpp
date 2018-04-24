//
// Created by romain on 18/04/2018.
//

#include "NetworkBuffer.h"
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
    memcpy(&_buffer[_pos], reinterpret_cast<uint8_t *>(&to_copy), size);
    _pos += size;
}

std::vector<uint8_t> NetworkBuffer::readBytes() {
    int32_t count = readInt();
    std::vector<uint8_t> read;

    for (int i = 0; i < count; i++)
        read.push_back(_buffer[_pos + i]);
    _pos += count;
    return read;
}

template<typename T>
void NetworkBuffer::writeBytes(std::vector<T> &to_copy) {
    auto size = static_cast<int32_t>(to_copy.size());
    writeInt(static_cast<int32_t>(size));

    if (_pos + size > _buffer.size())
        _buffer.resize(_pos + size);
    memcpy(&_buffer[_pos], reinterpret_cast<uint8_t *>(&to_copy[0]), static_cast<size_t>(size));
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
    std::vector<uint8_t> read = readBytes();
    return std::string(read.begin(), read.end());
}

void NetworkBuffer::writeUtf(std::string value) {
    std::vector<uint8_t> asList(value.begin(), value.end());
    writeBytes(asList);
}

void NetworkBuffer::clear() {
    _buffer.clear();
    _pos = 0;
}

void NetworkBuffer::push_bytes(uint8_t const *bytes, ssize_t count) {
    for (int i = 0; (count == 0 || i < count) &&  bytes[i] != 0; ++i)
        _buffer.push_back(bytes[i]);
}