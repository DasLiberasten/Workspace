#ifndef __SOCK_CLIENT_H__
#define __SOCK_CLIENT_H__

#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

    enum ExceptionType {
        ESE_SOCKCREATE,
        ESE_SOCKCONN,
        ESE_SOCKSEND,
        ESE_SOCKRECV,
    };

    class SocketException {
    public:
        std::string message;

        explicit SocketException(ExceptionType);

        void MyReport() const;

        ~SocketException() = default;
    };

    class BaseSocket {
    protected:
        int MySocket = -1;
        struct sockaddr_un Sock;
    public:
        void putChar(char) const;

        void putString(const char *);

        void putString(const std::string &str);

        char getChar() const;

        std::string getString() const;

        void getTable() const;

        ~BaseSocket() = default;
    };

    class ClientSocket : public BaseSocket {
    public:
        explicit ClientSocket(const char *);

        void MyConnect();

        ~ClientSocket();
    };
#endif
