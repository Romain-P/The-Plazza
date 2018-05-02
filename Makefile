CXXFLAGS += -Wall -Werror -Wextra -std=c++17
CXXFLAGS += -I inc/

SRC	=	src/Main.cpp                                        \
        src/Logger.cpp                                      \
        src/handlers/MasterPacketHandler.cpp                \
        src/handlers/SlavePacketHandler.cpp                 \
        src/netwotk/AbstractPacketHandler.cpp               \
        src/netwotk/NetworkBuffer.cpp                       \
        src/netwotk/NetworkClient.cpp                       \
        src/netwotk/NetworkProtocol.cpp                     \
        src/netwotk/NetworkServer.cpp                       \
        src/process/SlaveWorker.cpp                         \
        src/process/Task.cpp                                \
        src/process/TaskDispatcher.cpp                      \
        src/process/ThreadPoolExecutor.cpp                  \
        src/process/Timer.cpp                               \
        src/protocol/DestroyProcessMessage.cpp              \
        src/protocol/FreePlaceMessage.cpp                   \
        src/protocol/SearchRequestMessage.cpp               \
        src/protocol/SearchResultMessage.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	= 	plazza

$(NAME): $(OBJ)
	g++ $(OBJ) -pthread -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all