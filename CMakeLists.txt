cmake_minimum_required(VERSION 3.10)
project(Plazza)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
find_package (Threads)

add_executable(include/Shared.h src/Main.cpp src/netwotk/NetworkServer.cpp include/NetworkServer.h include/NetworkMessage.h src/netwotk/NetworkBuffer.cpp include/NetworkBuffer.h include/NetworkProtocol.h src/netwotk/NetworkClient.cpp src/netwotk/NetworkClient.cpp include/NetworkClient.h src/netwotk/AbstractPacketHandler.cpp include/AbstractPacketHandler.h src/netwotk/NetworkProtocol.cpp src/handlers/MasterPacketHandler.cpp src/handlers/MasterPacketHandler.cpp include/MasterPacketHandler.h src/protocol/SearchRequestMessage.cpp include/SearchRequestMessage.h src/handlers/SlavePacketHandler.cpp include/SlavePacketHandler.h src/protocol/SearchRequestMessage.cpp include/SearchRequestMessage.h include/SearchResultMessage.h src/protocol/SearchResultMessage.cpp src/process/TaskDispatcher.cpp include/TaskDispatcher.h src/protocol/FreePlaceMessage.cpp include/FreePlaceMessage.h src/process/Task.cpp include/Task.h src/process/SlaveWorker.cpp include/SlaveWorker.h src/Logger.cpp include/Logger.h src/process/ThreadPoolExecutor.cpp include/ThreadPoolExecutor.h src/protocol/DestroyProcessMessage.cpp include/DestroyProcessMessage.h src/process/Timer.cpp include/Timer.h src/crypto/XorCipher.cpp include/XorCipher.h src/protocol/ConnectSuccessMessage.cpp include/ConnectSuccessMessage.h)
target_link_libraries (Plazza ${CMAKE_THREAD_LIBS_INIT})