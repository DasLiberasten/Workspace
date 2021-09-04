#ifndef MY_CLIENT_EXECUTOR_H
#define MY_CLIENT_EXECUTOR_H


#include "Poliz.h"
#include "Analyzer.h"
#include "Database.h"
#include <stack>
#include <vector>
#include <cstring>
#include <iostream>
#include "Sock_serv.h"

extern bool vivod;
class Interpretator{
    Lex current;
    int id;
    string name;
    Table table;
    int size;
    Parser p;
    stack<long> int_args;
    stack<string> str_args;
    void gp(){
        id++;
        current = p.poliz[id];
    }
    void expr(Poliz& poliz, size_t row);
    vector<bool> where();
    void execute();
public:
    Interpretator(const char *program): p(program){
        id = 0;
        size = 0;
    }
    void Interpret(){
        p.analyze();
        size = p.poliz.get_size_cur();
        execute();
    }
    ~Interpretator(){
        int_args.;
    }
};


#endif //MY_CLIENT_EXECUTOR_H
