//
// Created by romain on 03/05/18.
//

#include "XorCipher.h"

/*
 * @see header for doc.
 */
namespace XorCipher {
    void process(std::string &data, char key) {
        size_t size = data.size();

        for (size_t i = 0; i < size; ++i)
            data[i] ^= key;
    }

    void bruteforce(const std::string &data, const std::function<bool(std::string &)> &callback) {
        std::string tmp;
        for (unsigned char c=0; c < 255; ++c) {
            tmp = std::string(data);
            process(tmp, c);
            if (callback(tmp))
                break;
        }
    }

    bool maybeCiphered(const std::string &data) {
        for (char c: data)
            if (!isprint(c) && c != '\n')
                return true;
        return false;
    }
}