cmake_minimum_required(VERSION 3.10)
project(Plazza)

set(CMAKE_CXX_STANDARD 17)
include_directories(inc)
find_package (Threads)

add_executable(Plazza inc/Shared.h src/Main.cpp src/netwotk/NetworkServer.cpp inc/NetworkServer.h inc/NetworkMessage.h src/netwotk/NetworkBuffer.cpp inc/NetworkBuffer.h inc/NetworkProtocol.h src/netwotk/NetworkClient.cpp src/netwotk/NetworkClient.cpp inc/NetworkClient.h src/netwotk/AbstractPacketHandler.cpp inc/AbstractPacketHandler.h src/netwotk/NetworkProtocol.cpp src/handlers/MasterPacketHandler.cpp src/handlers/MasterPacketHandler.cpp inc/MasterPacketHandler.h src/protocol/SearchRequestMessage.cpp inc/SearchRequestMessage.h src/handlers/SlavePacketHandler.cpp inc/SlavePacketHandler.h src/protocol/SearchRequestMessage.cpp inc/SearchRequestMessage.h inc/SearchResultMessage.h src/protocol/SearchResultMessage.cpp src/process/TaskDispatcher.cpp inc/TaskDispatcher.h src/protocol/FreePlaceMessage.cpp inc/FreePlaceMessage.h src/process/Task.cpp inc/Task.h src/process/SlaveWorker.cpp inc/SlaveWorker.h src/Logger.cpp inc/Logger.h src/process/ThreadPoolExecutor.cpp inc/ThreadPoolExecutor.h src/protocol/DestroyProcessMessage.cpp inc/DestroyProcessMessage.h src/process/Timer.cpp inc/Timer.h)
target_link_libraries (Plazza ${CMAKE_THREAD_LIBS_INIT})