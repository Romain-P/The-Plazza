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

#       define SOCKET_ERROR -1
#       define close_socket(s) close (s)

        typedef int session_t;
        typedef struct sockaddr_in insocket_t;
        typedef struct sockaddr socket_t;
#   endif

        typedef struct pollfd pollfd_t;

#include <mutex>
#include <shared_mutex>
#include <vector>

using lock_t = std::lock_guard<std::mutex>;
        using write_lock_t = std::unique_lock<std::shared_mutex>;
        using read_lock_t = std::shared_lock<std::shared_mutex>;

namespace util {
    static std::vector<std::string> split(char *phrase, const std::string &delimiter) {
            std::vector<std::string> list;
            std::string s(phrase);
            size_t pos = 0;
            std::string token;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                    token = s.substr(0, pos);
                    list.push_back(token);
                    s.erase(0, pos + delimiter.length());
            }
            return list;
    }
}
#endif //PLAZZA_SHARED_H
