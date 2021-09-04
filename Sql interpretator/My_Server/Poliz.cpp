#include <algorithm>
#include "Poliz.h"

std::string Poliz::TW[] = { "NULL",
                       "AND", "SELECT", "LOGIC", "INSERT", "UPDATE",
                       "DELETE", "LONG", "NOT", "OR", "CREATE",
                       "DROP", "WHERE", "TABLE", "INTO", "FROM",
                       "SET", "IN", "ALL", "TEXT", "EXIT", "#"
};

std::string Poliz::TD[] = {"NULL",
                      "\'", ",", "(", ")", "=", "<", ">",
                      "+", "-", "*", "/", "<=", "!=", ">="
};


int Poliz::check(const std::string &buf, std::string *list, int n) {
    int i = 0;
    while (i < n) {
        if (buf == list[i]) {
            return i;
        }
        i++;
    }
    return 0;
}

Lex Poliz::get_lex(){
    enum state{
        H,
        IDENT,   // Идентификатор (переменная)
        NUMB,    // Число
        COM,     // Комментарий
        ALE,     // < > = <= >=
        NEQ,     // !=
        LETTER,  // "string"
    };
    state CS = H;
    std::string buf;
    int d = 0, j, sign_flag = 1,c;

    do{
        c = gc();
        switch(CS){
            case H:
                if(c == ' ' || c == '\n' || c == '\r' || c == '\t'){}
                else if(isalpha(c) || c == '{' || c == '}'){
                    buf.push_back(c);
                    CS = IDENT;
                }
                else if(isdigit(c)){
                    d = c - '0';
                    CS = NUMB;
                }
                else if (c == '\''){
                    CS = LETTER;
                }
                else if(c == '-'){
                    sign_flag = -1;
                    CS = NUMB;
                }
                else if(c == '#'){
                    CS = COM;
                }
                else if(c == '=' || c == '<' || c == '>'){
                    buf.push_back(c);
                    CS = ALE;
                }
                else if ( c == '!' ) {
                    buf.push_back(c);
                    CS = NEQ;
                }
                else {
                    buf.push_back(c);
                    if((j = check( buf, TD, TDlen))){
                        return Lex((Lex_type) (j - 1 + (int) LEX_EXIT), j, buf);
                    }

                    else throw c;
                }
                break;

            case IDENT:
                if(isalpha(c) || isdigit(c) || c == '_'){
                    buf.push_back(c);
                }
                else{
                    workspace = (char)c + workspace;
                    if((j = check(buf, TW, TWlen))){//Если это лексема
                        return Lex ((Lex_type) j , j, buf );
                    }
                    else{//Если это переменная
                        return Lex(LEX_ID, LEX_ID, buf);
                    }
                }
                break;

            case NUMB:
                if(isdigit(c)){//наращиваем цифру
                    d = d * 10 + (c - '0');
                }
                else if(sign_flag==-1 && d==0){//если после минуса ничего
                    workspace = (char)c + workspace;
                    j = check(buf, TD, TDlen);
                    return Lex(LEX_MINUS, j, "-");
                }
                else{
                    workspace = (char)c + workspace;
                    d *= sign_flag;
                    sign_flag = 1;
                    return Lex(LEX_NUM, d, "NUM");
                }
                break;
            case COM:
                if(c == '\n'){
                    CS = H;
                }
                else if(c == '#') throw c;
                break;
            case ALE:
                if(c == '='){
                    buf.push_back(c);
                    j = check(buf, TD, TDlen);
                    return Lex((Lex_type) (j - 1 + (int) LEX_EXIT), j, buf );
                }
                else {
                    workspace = (char)c + workspace;
                    j = check(buf, TD, TDlen);
                    return Lex ((Lex_type) ( j - 1 + (int) LEX_EXIT), j, buf );
                }
                break;
            case NEQ:
                if(c == '='){
                    buf.push_back(c);
                    j = check(buf, TD, TDlen);
                    return Lex(LEX_NEQ, j, buf);
                }
                else throw '!';
                break;
            case LETTER:
                if(c == '\''){
                    CS = H;
                    return Lex(LEX_LETTER, LEX_LETTER , buf);
                }
                else {
                    buf.push_back(c);
                }
                break;
            default:break;
        }
    }
    while (true);
}

Lex& Poliz::operator[](int index){
    if(index > get_size_max())
        throw "POLIZ: out of array range";
    else
        return lexeme[index];
}

int Poliz::get_size_max() const {
    return size_max;
};