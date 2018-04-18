cmake_minimum_required(VERSION 3.10)
project(plazza)

set(CMAKE_CXX_STANDARD 11)
include_directories(inc)

add_executable(plazza inc/Shared.h src/Main.cpp src/NetworkServer.cpp inc/NetworkServer.h)