//
// Created by romain on 18/04/2018.
//

#ifndef PLAZZA_SHARED_H
#   define PLAZZA_SHARED_H
#   define linux

#   if defined (WIN32)
#       include <winsock2.h>
        typedef int socklen_t;
#   elif defined (linux)
#       include <sys/types.h>
#       include <sys/socket.h>
#       include <netinet/in.h>
#       include <arpa/inet.h>
#       include <unistd.h>

#       define SOCKET_ERROR -1
#       define close_socket(s) close (s)

        typedef int session_t;
        typedef struct sockaddr_in insocket_t;
        typedef struct sockaddr socket_t;
#   endif

#endif //PLAZZA_SHARED_H
