//
// Created by romain on 03/05/18.
//

#ifndef PLAZZA_XORCIPHER_H
#define PLAZZA_XORCIPHER_H


#include <string>
#include <functional>

namespace XorCipher {
    /**
     * Crypt/Decrypt a given data
     *
     * @param data  ciphered or plain text
     * @param key   key to decrypt
     */
    void process(std::string &data, char key);

    /**
     * Reverse a given ciphered text with the 255 chars.
     * Each reverse is sent to the callback.
     *
     * @param data      ciphered text
     * @param callback  return true to break bruteforce
     */
    void bruteforce(const std::string &data, const std::function<bool(std::string &)> &callback);

    /**
     *
     * @param data  data to test
     * @return      true if the data seems to be ciphered
     */
    bool maybeCiphered(const std::string &data);
};


#endif //PLAZZA_XORCIPHER_H
