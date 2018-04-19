//
// Created by romain on 18/04/2018.
//

#include <cstdio>
#include <NetworkServer.h>
#include "Shared.h"
#include <csignal>

void test() {

}

int main() {
    NetworkServer server;
    std::thread &thread(server.init());
    thread.join();
}