//
// Created by romain on 18/04/2018.
//

#ifndef PROJECT_NETWORKBUFFER_H
#define PROJECT_NETWORKBUFFER_H

class NetworkBuffer {
public:
    NetworkBuffer() : _buffer(), _pos(0) {}

    template<typename T>
    void readBytes(T &to_fill);

    template<typename T>
    void writeBytes(T &to_copy);

    int32_t readInt();
    void writeInt(int32_t value);

    std::string readUtf();
    void writeUtf(std::string str);

private:
    std::vector<char> _buffer;
    size_t _pos;
};

#endif //PROJECT_NETWORKBUFFER_H