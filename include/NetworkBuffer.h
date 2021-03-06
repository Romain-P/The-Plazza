//
// Created by romain on 18/04/2018.
//

#ifndef PROJECT_NETWORKBUFFER_H
#define PROJECT_NETWORKBUFFER_H

#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>

class NetworkBuffer {
public:
    NetworkBuffer() : _buffer(), _pos(0) {}

    template<typename T>
    void readBytes(T &to_fill);

    std::vector<uint8_t> readBytes();

    template<typename T>
    void writeBytes(T &to_copy);

    template<typename T>
    void writeBytes(std::vector<T> &to_copy);

    void writeBool(bool value);
    bool readBool();

    int32_t readInt();
    void writeInt(int32_t value);

    std::string readUtf();
    void writeUtf(std::string str);

    void clear();
    void push_bytes(uint8_t const *bytes, ssize_t count = 0);

    std::vector<uint8_t> &getBytes();
private:
    std::vector<uint8_t> _buffer;
    size_t _pos;
};

#endif //PROJECT_NETWORKBUFFER_H
