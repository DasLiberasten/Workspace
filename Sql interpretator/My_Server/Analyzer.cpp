#include "Analyzer.h"
#include "Poliz.h"
#include "Database.h"

void Parser::START() {
        while (lexType == LEX_SELECT || lexType == LEX_INSERT || lexType == LEX_UPDATE
               || lexType == LEX_DELETE || lexType == LEX_CREATE || lexType == LEX_DROP) {
            switch (lexType) {
                case LEX_DROP: //
                    poliz.put_lex(cur);
                    gl();
                    DROP();
                    poliz.put_lex(POLIZ_SENTENCE);
                    break;
                case LEX_SELECT: //
                    poliz.put_lex(cur);
                    gl();
                    SELECT();
                    poliz.put_lex(POLIZ_SENTENCE);
                    break;
                case LEX_INSERT: //
                    poliz.put_lex(cur);
                    gl();
                    INSERT();
                    poliz.put_lex(POLIZ_SENTENCE);
                    break;
                case LEX_UPDATE://
                    poliz.put_lex(cur);
                    gl();
                    UPDATE();
                    poliz.put_lex(POLIZ_SENTENCE);
                    break;
                case LEX_DELETE: //
                    poliz.put_lex(cur);
                    gl();
                    DELETE();
                    poliz.put_lex(POLIZ_SENTENCE);
                    break;
                case LEX_CREATE: //
                    poliz.put_lex(cur);
                    gl();
                    CREATE();
                    poliz.put_lex(POLIZ_SENTENCE);
                    break;
                default:
                    throw cur;
            }
        }

        if (lexType != LEX_EXIT)
            throw cur;
}
void Parser::DROP() {
    if (lexType == LEX_TABLE) {
        gl();
    } else
        throw cur;

    if (lexType == LEX_ID) {
        poliz.put_lex(Lex(LEX_TABLENAME, LEX_TABLENAME, cur.get_name()));
        table_name = cur.get_name();
        gl();
    } else throw cur;
}
void Parser::SELECT() {
    //<список полей>
    stack<string> buf;
    if (lexType == LEX_TIMES) { //all (*)
        poliz.put_lex(Lex(LEX_ALLCOLS, LEX_ALLCOLS, "*"));
        gl();
    } else if (lexType == LEX_ID) { //IDENT
        while (true) {
            if (lexType != LEX_ID) throw cur;
            buf.push(cur.get_name());
            poliz.put_lex(cur);
            gl();
            if (lexType != LEX_COMMA) break;
            gl();
        }
    } else throw cur;
    if (lexType == LEX_FROM) {
        poliz.put_lex(cur);
        gl();
    } else throw cur;
    if (lexType == LEX_ID) {
        poliz.put_lex(Lex(LEX_TABLENAME, LEX_TABLENAME, cur.get_name()));
        table_name = cur.get_name();
        gl();
    } else throw cur;
    check_stack(buf);
    WHERE();
}
void Parser::INSERT() {
    if (lexType == LEX_INTO)
        gl();
    else
        throw cur;
    if (lexType == LEX_ID) {
        poliz.put_lex(Lex(LEX_TABLENAME, LEX_TABLENAME, cur.get_name()));
        gl();
    } else throw cur;

    if (lexType == LEX_LPAREN) {
        gl();
        while (true) {
            if (lexType == LEX_LETTER || lexType == LEX_NUM)
                poliz.put_lex(cur);
            else throw cur;
            gl();
            if (lexType != LEX_COMMA) break;
            gl();
        }
        if (lexType != LEX_RPAREN)
            throw cur;
        gl();
    } else throw cur;
}
void Parser::UPDATE() {
    if (lexType == LEX_ID) {
        poliz.put_lex(Lex(LEX_TABLENAME, LEX_TABLENAME, cur.get_name()));
        table_name = cur.get_name();
        gl();
    } else throw cur;

    if (lexType == LEX_SET)
        gl();
    else throw cur;

    if (lexType == LEX_ID) {
        check_id(cur.get_name());
        poliz.put_lex(cur);
        check_id(cur.get_name());
        gl();
    } else throw cur;

    if (lexType == LEX_EQ)
        gl();
    else throw cur;

    EQUALATION();
    check_eq();
    WHERE();
}
void Parser::DELETE() {
    if (lexType == LEX_FROM)
        gl();
    else throw cur;

    if (lexType == LEX_ID) {
        poliz.put_lex(Lex(LEX_TABLENAME, LEX_TABLENAME, cur.get_name()));
        table_name = cur.get_name();
        gl();
    } else throw cur;
    WHERE();
}
void Parser::CREATE() {
    if (lexType == LEX_TABLE)
        gl();
    else throw cur;

    if (lexType == LEX_ID) {
        poliz.put_lex(cur);
        gl();
    } else throw cur;

    if (lexType == LEX_LPAREN) {
        gl();
        W();
        poliz.incNum();
        while (lexType == LEX_COMMA) { // ,
            gl();
            W();
            poliz.incNum();
        }
        if (lexType != LEX_RPAREN) {
            throw cur;
        }
        gl();
    } else throw cur;
}
void Parser::W() {
    if (lexType == LEX_ID) {
        names.push(cur_val);
        poliz.put_lex(cur);
        gl();
    } else
        throw cur;

    switch (lexType) {
        case LEX_TEXT:
            poliz.put_lex(cur);
            gl();
            if (lexType == LEX_LPAREN)
                gl();
            else throw cur;

            if (lexType == LEX_NUM) {
                poliz.put_lex(cur);
                gl();
            } else throw cur;
            if (lexType != LEX_RPAREN)
                throw cur;
            break;

        case LEX_LONG:
            poliz.put_lex(cur);
            break;

        default:
            throw cur;
    }
    gl();
}
void Parser::WHERE() {
    if(lexType == LEX_WHERE){
        poliz.put_lex(cur);
        gl();

        if(lexType == LEX_ALL){
            poliz.put_lex(cur);
            gl();
        }
        else{
            EQUALATION();
            if(arifm.top() != LEX_LOGIC){
                if(lexType == LEX_NOT){
                    poliz.put_lex(cur);
                    gl();
                }

                if(lexType == LEX_IN){
                    poliz.put_lex(cur);
                    gl();
                }else
                    throw cur;

                if(lexType == LEX_LPAREN){
                    gl();
                    if(lexType == LEX_NUM){
                        arifm.push(LEX_LONG);
                        poliz.put_lex(cur);
                        gl();
                        while (lexType == LEX_COMMA){ // ,
                            gl();
                            if(lexType == LEX_NUM)
                                poliz.put_lex(cur);
                            else
                                throw cur;
                            gl();
                        }
                    }else{
                        if(lexType == LEX_LETTER){
                            arifm.push(LEX_TEXT);
                            poliz.put_lex(cur);
                        }else
                            throw cur;
                        gl();
                        while (lexType == LEX_COMMA){ // ,
                            gl();
                            if(lexType == LEX_LETTER)
                                poliz.put_lex(cur);
                            else
                                throw cur;
                            gl();
                        }
                    }
                    if(lexType != LEX_RPAREN){
                        throw cur;
                    }
                    check_eq();
                    gl();
                }else throw cur;
            }
            else{
                arifm.pop();
            }
        }
    }else throw cur;
}
void Parser::EQUALATION() {//Операции сравнения
    SECONDPRI();
    if((lexType == LEX_EQ) || (lexType == LEX_LSS) || (lexType == LEX_GTR) ||
       (lexType == LEX_LEQ) || (lexType == LEX_GEQ) || (lexType == LEX_NEQ)){
        arifm.push(lexType);
        gl();
        SECONDPRI();
        check_logic();
    }
}
void Parser::SECONDPRI() {// low priority lexemes
    FIRSTPRI();
    while((lexType == LEX_PLUS) || (lexType == LEX_MINUS) || (lexType == LEX_OR)){
        arifm.push(lexType);
        gl();
        FIRSTPRI();
        check_logic();
    }
}
void Parser::FIRSTPRI() { //выше приоритет чем у сложения
    FACTOR();
    gl();
    while((lexType == LEX_TIMES) || (lexType == LEX_AND) || (lexType == LEX_SLASH) || (lexType == LEX_MOD)){
        arifm.push(lexType);
        gl();
        FACTOR();
        check_logic();
        gl();
    }
}
void Parser::FACTOR() {
    switch(lexType){
        case LEX_ID:
            check_id(cur.get_name());
            poliz.put_lex(cur);
            break;

        case LEX_NUM:
            arifm.push(LEX_LONG);
            poliz.put_lex(cur);
            break;

        case LEX_LETTER:
            arifm.push(LEX_TEXT);
            poliz.put_lex(cur);
            break;

        case LEX_NOT:
            gl();
            FACTOR();
            check_not();
            break;

        case LEX_LPAREN:
            gl();
            EQUALATION();
            if (lexType != LEX_RPAREN)
                throw cur;
            break;

        default:
            throw cur;
    }
}
template <typename T, typename T_EL> void from_st(T& t, T_EL & x){
    x = t.top();
    t.pop();
}
void Parser::check_id(const string& lexname){//Есть ли такая колонка?
    Table a;
    a.open_table(table_name);
    if(a.find_record(lexname) == TEXT)
        arifm.push(LEX_TEXT);
    else if(a.find_record(lexname) == LONG)
        arifm.push(LEX_LONG);
    else {
        a.close_table(table_name);
        throw "ERROR: not declared";
    }

    a.close_table(table_name);
}
void Parser::check_logic(){//ПРОВЕРКА ТИПА РЕЗУЛЬТАТА
    Lex_type t1, t2, op, res = LEX_LOGIC;
    from_st(arifm, t2);
    from_st(arifm, op);
    from_st(arifm, t1);

    if(op == LEX_PLUS || op == LEX_MINUS || op == LEX_TIMES || op == LEX_SLASH || op == LEX_MOD)
        res = LEX_LONG;

    if(op == LEX_OR || op == LEX_AND || op == LEX_EQ || op == LEX_LSS || op == LEX_GTR || op == LEX_LEQ || op == LEX_GEQ)
        res = LEX_LOGIC;

    if ((res == LEX_LONG && t1 == LEX_LONG && t2 == LEX_LONG) ||
            (res == LEX_LOGIC && (op == LEX_OR || op == LEX_AND) && t1 == LEX_LOGIC && t2 == LEX_LOGIC) ||
            (res == LEX_LOGIC && (op == LEX_EQ || op == LEX_LSS || op == LEX_GTR || op == LEX_LEQ || op == LEX_GEQ) && t1 == LEX_TEXT && t2 == LEX_TEXT) ||
            (res == LEX_LOGIC && (op == LEX_EQ || op == LEX_LSS || op == LEX_GTR || op == LEX_LEQ || op == LEX_GEQ) && t1 == LEX_LONG && t2 == LEX_LONG)){
        arifm.push(res);
        poliz.put_lex(op);
    }
    else throw "wrong types in operation";
}
void Parser::check_not(){
    if(arifm.top() != LEX_LOGIC)
        throw "NOT requires logical statement";
    else
        poliz.put_lex(Lex(LEX_NOT));
}
void Parser::check_eq(){
    Lex_type t;
    from_st(arifm, t);
    if(t != arifm.top())
        throw "wrong types in =";
    arifm.pop();
}
void Parser::check_stack(stack<string> buf) const {
    Table a;
    a.open_table(table_name);
    string t;
    while(!buf.empty()){
     t = buf.top();
     buf.pop();
     if(a.find_record(t) == NONE) {
         a.close_table(table_name);
         throw "ERROR: not declared";
     }
    }
    a.close_table(table_name);
}
