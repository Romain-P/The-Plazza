//
// Created by romain on 18/04/2018.
//

#include <cstdio>
#include "NetworkServer.h"
#include "Shared.h"
#include <csignal>
#include "SlavePacketHandler.h"
#include "MasterPacketHandler.h"

void test() {

}

int main() {
    //tests
    ServerHandler serverHandler;
    ClientHandler clientHandler;

    serverHandler.init();
    clientHandler.init();

    NetworkServer server;
    std::thread &thread(server.init());
    thread.join();
}