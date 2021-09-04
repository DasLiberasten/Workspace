#ifndef MY_CLIENT_ANALYZER_H
#define MY_CLIENT_ANALYZER_H

#include "Poliz.h"

#include <stack>

using namespace std;

class Parser{
    stack<int>names;// стек с именами колонок
    stack<Lex_type>arifm;//тип лексем для грамотной арифметики
    Lex cur;
    Lex_type lexType;
    int cur_val;
    void START();
    void DROP();
    void SELECT();
    void INSERT();
    void UPDATE();
    void DELETE();
    void CREATE();
    void WHERE();
    void EQUALATION();
    void SECONDPRI();
    void FIRSTPRI();
    void FACTOR();
    void W();
    void check_id(const string&);
    void check_stack(stack<string>) const;
    void check_logic();
    void check_not();
    void check_eq();
    void gl(){
        cur = poliz.get_lex ();
        lexType = cur.get_type();
        cur_val = cur.get_id();
    }
public:
    Poliz poliz;
    string table_name;
    Parser(const char *program):poliz(1000,program){};
    void analyze(){
        gl();
        START();
    }
};



#endif //MY_CLIENT_ANALYZER_H
