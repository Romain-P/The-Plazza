//
// Created by romain on 29/04/18.
//

#ifndef PLAZZA_LOGGER_H
#define PLAZZA_LOGGER_H


#include <string>
#include <NetworkMessage.h>

class Logger {
public:
    static void init(int indicator = -1, bool file_log = false, bool stdout_log = false, bool slave = false);
    static void log(std::string const &str);
    static void log(NetworkMessage const &msg);
    static void log(std::string const &str, NetworkMessage const &msg);

    static void recv(int slave_id, NetworkMessage const &msg);
    static void sent(int slave_id, NetworkMessage const &msg);
private:
    static int INDICATOR;
    static bool SLAVE;
    static bool LOGFILE;
    static bool LOGOUT;

    static void header();
};


#endif //PLAZZA_LOGGER_H
