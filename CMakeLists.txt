cmake_minimum_required(VERSION 3.5)
project(plazza)

set(CMAKE_CXX_STANDARD 14)
include_directories(inc)
find_package (Threads)

add_executable(plazza inc/Shared.h src/Main.cpp src/NetworkServer.cpp inc/NetworkServer.h inc/NetworkMessage.h src/NetworkBuffer.cpp inc/NetworkBuffer.h inc/NetworkProtocol.h src/NetworkClient.cpp src/NetworkClient.cpp inc/NetworkClient.h src/protocol/HelloConnectMessage.cpp src/protocol/HelloConnectMessage.cpp inc/HelloConnectMessage.h src/PacketHandler.cpp inc/PacketHandler.h src/NetworkProtocol.cpp)
target_link_libraries (plazza ${CMAKE_THREAD_LIBS_INIT})