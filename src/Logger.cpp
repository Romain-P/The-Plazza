//
// Created by romain on 29/04/18.
//

#include <iostream>
#include "Logger.h"

int Logger::INDICATOR = -1;
bool Logger::SLAVE = false;
bool Logger::LOGFILE = false;
bool Logger::LOGOUT = false;

void Logger::init(int indicator, bool file_log, bool stdout_log, bool slave) {
    INDICATOR = indicator;
    SLAVE = slave;
    LOGFILE = file_log;
}

void Logger::log(std::string const &str) {
    if (!LOGOUT) return;
    header();
    std::cout << str.c_str() << std::endl;
}

void Logger::log(std::string const &str, NetworkMessage const &msg) {
    if (!LOGOUT) return;
    header();
    std::cout << str.c_str() << msg << std::endl;
}

void Logger::log(NetworkMessage const &msg) {
    if (!LOGOUT) return;
    header();
    std::cout << msg << std::endl;
}

void Logger::header() {
    if (SLAVE)
        std::cout << "[SLAVE " << INDICATOR << "] ";
    else
        std::cout << "[MASTER] ";
}
