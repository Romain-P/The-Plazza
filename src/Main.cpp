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

static void launch_server(size_t threadpool_size, char *bin) {
    MasterPacketHandler masterHandler;
    NetworkServer server(&masterHandler);
    TaskDispatcher dispatcher(server, threadpool_size, bin);

    masterHandler.setTaskDispatcher(&dispatcher);
    masterHandler.init();

    std::thread &thread(server.init());
    thread.join();
}

int main(int ac, char *argv[]) {
    size_t thread_pool_size;

    if (ac == 3 && strcmp(argv[1], TaskDispatcher::SLAVE_MOD) == 0) {
        int serverPort = atoi(argv[2]);
        //TODO: slave exec
    } else if (ac < 2 || (thread_pool_size = static_cast<size_t>(atoi(argv[1]))) <= 0) {
        std::cerr << "invalid arguments, please specify a valid thread pool size" << std::endl;
        return 84;
    } else
        launch_server(thread_pool_size, argv[0]);

    return 0;
}