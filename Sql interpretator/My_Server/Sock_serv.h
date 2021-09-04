#ifndef __SOCK_SERV_H__
#define __SOCK_SERV_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>

    enum ExceptionType {
        ESE_SOCKCREATE,
        ESE_SOCKSEND,
        ESE_SOCKRECV,
        ESE_SOCKBIND,
        ESE_SOCKLISTEN,
        ESE_SOCKACCEPT
    };
    class BaseSocket {
    protected:
        int MySocket = -1;
        struct sockaddr_un Sock;
    public:
        explicit BaseSocket(int sd = -1, const char *address = nullptr);

        void putChar(char) const;

        void putString(const char *);

        void putString(const std::string &str);

        char getChar() const;

        std::string getString() const;

        ~ BaseSocket() = default;
    };
    extern BaseSocket *pSocket;
    class ServerSocket : public BaseSocket {
    public:
        explicit ServerSocket(const char *);

        void MyBind();

        void MyListen(int);

        BaseSocket *MyAccept();

        ~ServerSocket();
    };

    class SocketException {
    public:
        std::string message;

        explicit SocketException(ExceptionType);

        void MyReport(BaseSocket *) const;

        ~SocketException() = default;
    };

#endif
