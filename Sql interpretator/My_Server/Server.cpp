#include "Sock_serv.h"
#include "Database.h"
#include "Executor.h"

const char *address = "Sock_name";
BaseSocket *pSocket = nullptr;
bool vivod = false;
int main() {
    try {
        srand(time(nullptr));
        remove(address);
        Table b;
        ServerSocket sock(address);
        pSocket = sock.MyAccept();
        std::string str;
        std::string f_name;
        while (true) {
            try {
                f_name = pSocket->getString();
                if (f_name == "END") {
                    pSocket->putString("Bye;");
                    delete pSocket;
                    return 0;
                }
                f_name += "\nEXIT";
                Interpretator I(f_name.c_str()); //
                I.Interpret();
                if (vivod)
                    vivod = false;
                else
                    pSocket->putString("OK;");
            }
            catch (TableException &err) {
                err.report(pSocket);
            }
            catch (SocketException &err) {
                err.MyReport(pSocket);
            }
            catch (Lex &err){
                pSocket->putString(err.get_name()+";");
            }
            catch (const char *err){
                pSocket->putString(err);
            }
            catch (const int &err){
                pSocket->putString(";");
            }
        }
    }
    catch (SocketException &err) {
        err.MyReport(pSocket);
    }
    return 0;
}

