//
// Created by romain on 18/04/2018.
//

#ifndef PROJECT_NETWORKBUFFER_H
#define PROJECT_NETWORKBUFFER_H

class NetworkBuffer {
public:
    int32_t read_int();
    std::string read_utf();

private:
    std::vector<unsigned char> _buffer;
    size_t _pos;
};

#endif //PROJECT_NETWORKBUFFER_H
