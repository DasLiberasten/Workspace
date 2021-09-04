#include "Sock_client.h"

const char *address = "/home/nikita/CLionProjects/My_Server/cmake-build-debug/Sock_name";

int main() {
    try {
        ClientSocket sock(address);
        std::string str;
        while (str != "END") {
            std::cout << "\n> ";
            getline(std::cin, str);
            sock.putString(str);
            std::cout << sock.getString();
        }
    }
    catch (SocketException &e) {
        e.MyReport();
    }
    return 0;
}
