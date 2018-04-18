//
// Created by romain on 18/04/2018.
//

#include <cstdio>
#include <NetworkServer.h>
#include "Shared.h"

int main() {
    NetworkServer server;

    std::thread &thread(server.init());

    for (int i=0; i < 10000;++i) {
        printf("test\n");
    }

    server.close_all();
    thread.join();
}