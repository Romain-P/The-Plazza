cmake_minimum_required(VERSION 3.5)
project(plazza)

set(CMAKE_CXX_STANDARD 14)
include_directories(inc)
find_package (Threads)

add_executable(plazza inc/Shared.h src/Main.cpp src/netwotk/NetworkServer.cpp inc/NetworkServer.h inc/NetworkMessage.h src/shared/NetworkBuffer.cpp inc/NetworkBuffer.h inc/NetworkProtocol.h src/netwotk/NetworkClient.cpp src/netwotk/NetworkClient.cpp inc/NetworkClient.h src/protocol/HelloConnectMessage.cpp src/protocol/HelloConnectMessage.cpp inc/HelloConnectMessage.h src/shared/AbstractPacketHandler.cpp inc/AbstractPacketHandler.h src/shared/NetworkProtocol.cpp src/handlers/MasterPacketHandler.cpp src/handlers/MasterPacketHandler.cpp inc/MasterPacketHandler.h src/protocol/AwesomeMessage.cpp inc/AwesomeMessage.h src/handlers/SlavePacketHandler.cpp inc/SlavePacketHandler.h src/protocol/AwesomeMessage.cpp inc/AwesomeMessage.h)
target_link_libraries (plazza ${CMAKE_THREAD_LIBS_INIT})