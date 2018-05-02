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
#include "Logger.h"

static bool sigint_catched = false;

static void read_commands(TaskDispatcher &dispatcher) {
    bool piped = !isatty(STDIN_FILENO);

    for (std::string line; std::getline(std::cin, line);) {
        dispatcher.parse_commands(line);
    }
    if (piped) {
        while (dispatcher.remains_tasks() && !sigint_catched);
    }
}

static void launch_server(size_t threadpool_size, char *bin) {
    Logger::init(-1, false, true, false);
    MasterPacketHandler masterHandler;
    NetworkServer server(&masterHandler);

    std::thread &thread(server.init());


    std::string threadp_size(std::to_string(threadpool_size));
    std::string server_port(std::to_string(server.getPort()));

    TaskDispatcher dispatcher(server, threadp_size, server_port, bin);
    masterHandler.setTaskDispatcher(&dispatcher);
    masterHandler.init();

    while (server.getSession() == -1);
    signal(SIGINT, [](int) {
        fclose(stdin);
        sigint_catched = true;
    });
    read_commands(dispatcher);
    server.stop();
    server.await_stop();
    thread.detach();
}

static void launch_slave(int serverPort, size_t threadpool_size) {
    SlavePacketHandler slaveHandler;
    auto client = NetworkClient::create(slaveHandler, static_cast<uint16_t>(serverPort));
    SlaveWorker worker(client.get(), threadpool_size);
    worker.init();
    slaveHandler.setSlaveWorker(&worker);
    slaveHandler.init();

    while (client->getSession() == -1);

    client->send(FreePlaceMessage(static_cast<int32_t>(threadpool_size * 2)));
    signal(SIGINT, [](int) {});
    client->getThread().join();
    worker.stop();
}

int main(int ac, char *argv[]) {
    size_t thread_pool_size;

    if (ac == 4 && strcmp(argv[1], TaskDispatcher::SLAVE_MOD) == 0) {
        int serverPort = atoi(argv[2]);
        thread_pool_size = static_cast<size_t>(atoi(argv[3]));

        launch_slave(serverPort, thread_pool_size);
    } else if (ac < 2 || (thread_pool_size = static_cast<size_t>(atoi(argv[1]))) <= 0) {
        std::cerr << "invalid arguments, please specify a valid thread pool size" << std::endl;
        return 84;
    } else
        launch_server(thread_pool_size, argv[0]);

    return 0;
}