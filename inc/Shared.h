//
// Created by romain on 18/04/2018.
//

#ifndef PLAZZA_SHARED_H
#   define PLAZZA_SHARED_H

#   if defined (WIN32)
#       include <winsock2.h>
        typedef int socklen_t;
#   elif defined (linux)
#       include <sys/types.h>
#       include <sys/socket.h>
#       include <netinet/in.h>
#       include <arpa/inet.h>
#       include <unistd.h>

#       define INVALID_SOCKET -1
#       define SOCKET_ERROR -1
#       define closesocket(s) close (s)

        typedef int SOCKET;
        typedef struct sockaddr_in SOCKADDR_IN;
        typedef struct sockaddr SOCKADDR;
#   endif

#endif //PLAZZA_SHARED_H
