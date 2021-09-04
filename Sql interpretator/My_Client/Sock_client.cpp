#include "Sock_client.h"

SocketException::SocketException(ExceptionType type) {
    switch (type) {
        case ESE_SOCKCREATE:
            message = "Error in socket create";
            break;
        case ESE_SOCKCONN:
            message = "Error in connect";
            break;
        case ESE_SOCKSEND:
            message = "Error in send";
            break;
        case ESE_SOCKRECV:
            message = "Error in recv";
            break;
        default:
            break;
    }
}

void SocketException::MyReport() const {
    std::cout << message << std::endl;
    std::cout << "Code: " << errno << std::endl;
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
        if (symbol == ';')
            break;
        str.push_back(symbol);
    }
    return str;
}

void BaseSocket::getTable() const {
    char symbol = ' ';
    while (symbol != EOF) {
        symbol = BaseSocket::getChar();
        if (symbol == ';')
            break;
        std::cout << symbol;
    }
}

ClientSocket::ClientSocket(const char *address) {
    int fd;
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1)
        throw SocketException(ESE_SOCKCREATE);
    MySocket = fd;
    Sock.sun_family = AF_UNIX;
    strcpy(Sock.sun_path, address);
    MyConnect();
}

void ClientSocket::MyConnect() {
    int s;
    s = connect(MySocket, (struct sockaddr *) &Sock, sizeof(Sock));
    if (s == -1)
        throw SocketException(ESE_SOCKCONN);
}

ClientSocket::~ClientSocket() {
    shutdown(MySocket, 2);
    close(MySocket);
}
