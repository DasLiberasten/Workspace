#include "Sock_serv.h"

SocketException::SocketException(ExceptionType type) {
    switch (type) {
        case ESE_SOCKCREATE:
            message = "Error in socket create;";
            break;
        case ESE_SOCKSEND:
            message = "Error in send;";
            break;
        case ESE_SOCKRECV:
            message = "Error in recv;";
            break;
        case ESE_SOCKBIND:
            message = "Error in bind;";
            break;
        case ESE_SOCKLISTEN:
            message = "Error in listen;";
            break;
        case ESE_SOCKACCEPT:
            message = "Error in accept;";
            break;
            default:
                break;
    }
}

void SocketException::MyReport(BaseSocket *sock) const {
    sock->putString(message);
}

BaseSocket::BaseSocket(int a1, const char *address) {
    MySocket = a1;
    if (address != nullptr) {
        Sock.sun_family = AF_UNIX;
        strcpy(Sock.sun_path, address);
    }
}

void BaseSocket::putChar(char symbol) const {
    int s;
    s = send(MySocket, (char *) &symbol, sizeof(char), 0);
    if (s == -1)
        throw SocketException(ESE_SOCKSEND);
}

void BaseSocket::putString(const char *str) {
    int s;
    s = send(MySocket, str, strlen(str) * sizeof(char), 0);
    if (s == -1)
        throw SocketException(ESE_SOCKSEND);
    if (str[strlen(str) - 1] != '\n')
        BaseSocket::putChar('\n');
}

void BaseSocket::putString(const std::string &str) {
    BaseSocket::putString(str.c_str());
}

char BaseSocket::getChar() const {
    char symbol;
    int s = 0;
    while (s == 0)
        s = recv(MySocket, (char *) &symbol, sizeof(char), 0);
    if (s == -1)
        throw SocketException(ESE_SOCKRECV);
    return symbol;
}

std::string BaseSocket::getString() const {
    std::string str;
    char symbol = ' ';
    while (symbol != EOF) {
        symbol = BaseSocket::getChar();
        if (symbol == '\n')
            break;
        str.push_back(symbol);
    }
    return str;
}

ServerSocket::ServerSocket(const char *address) {
    int fd;
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1)
        throw SocketException(ESE_SOCKCREATE);
    MySocket = fd;
    Sock.sun_family = AF_UNIX;
    strcpy(Sock.sun_path, address);
    MyBind();
    MyListen(1);
}

void ServerSocket::MyBind() {
    int s;
    s = bind(MySocket, (struct sockaddr *) &Sock, sizeof(Sock));
    if (s == -1)
        throw SocketException(ESE_SOCKBIND);
}

void ServerSocket::MyListen(const int backlog) {
    int s;
    s = listen(MySocket, backlog);
    if (s == -1)
        throw SocketException(ESE_SOCKLISTEN);
}

BaseSocket *ServerSocket::MyAccept() {
    int fd;
    fd = accept(MySocket, nullptr, nullptr);
    if (fd == -1)
        throw SocketException(ESE_SOCKACCEPT);
    auto *p = new BaseSocket(fd);
    return p;
}

ServerSocket::~ServerSocket() {
    shutdown(MySocket, 2);
    close(MySocket);
}

