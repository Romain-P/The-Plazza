//
// Created by romain on 18/04/2018.
//

#include <cstdio>
#include "NetworkServer.h"
#include "Shared.h"
#include <csignal>
#include <iostream>
#include <cstring>
#include "SlavePacketHandler.h"
#include "MasterPacketHandler.h"

void test() {

}

int main() {
    MasterPacketHandler masterHandler;
    SlavePacketHandler slaveHandler;

    masterHandler.init();
    slaveHandler.init();

    NetworkServer server(&masterHandler);
    std::thread &thread(server.init());
    thread.join();
}