#ifndef MY_CLIENT_POLIZ_H
#define MY_CLIENT_POLIZ_H

#include <stack>
#include <utility>
#include <vector>
#include <string>

#define TWlen 24
#define TDlen 15


enum Lex_type {
    LEX_NULL,       // NULL
    LEX_AND,        // AND
    LEX_SELECT,     // SELECT
    LEX_LOGIC,      // LOGIC
    LEX_INSERT,     // INSERT
    LEX_UPDATE,     // UPDATE
    LEX_DELETE,     // DELETE
    LEX_LONG,       // LONG
    LEX_NOT,        // NOT
    LEX_OR,         // OR
    LEX_CREATE,     // CREATE
    LEX_DROP,       // DROP
    LEX_WHERE,      // WHERE
    LEX_TABLE,      // TABLE
    LEX_INTO,       // INTO
    LEX_FROM,       // FROM
    LEX_SET,        // SET
    LEX_IN,         // INSERT
    LEX_ALL,        // ALL
    LEX_TEXT,       // TEXT
    LEX_EXIT,       // EXIT
    LEX_COMMA,      // ,
    LEX_LPAREN,     // (
    LEX_RPAREN,     // )
    LEX_EQ,         // =
    LEX_LSS,        // <
    LEX_GTR,        // >
    LEX_PLUS,       // +
    LEX_MINUS,      // -
    LEX_TIMES,      // *
    LEX_SLASH,      // /
    LEX_LEQ,        // <=
    LEX_NEQ,        // !=
    LEX_GEQ,        // >=
    LEX_MOD,        // %
    LEX_ALLCOLS,    // * (в таблице)
    LEX_NUM,        // число
    LEX_ID,         // идентификатор
    LEX_TABLENAME,  // имя таблицы
    LEX_LETTER,     // сообщение в кавычках
    POLIZ_SENTENCE, // конец SQL-предложения
};

class Lex {
    Lex_type typeOfLex;
    int id;
    std::string name;
public:
    Lex(Lex_type t = LEX_NULL, int v = 0, std::string n = "") {
        typeOfLex = t;
        id = v;
        name = std::move(n);
    }

    int get_id() const { return id; };

    std::string get_name() const { return name; };

    Lex_type get_type() const { return typeOfLex; };
};

class Poliz {
    Lex *lexeme;
    int size_max;
    int size_cur;
    std::string workspace;
    size_t num_of_ident;
public:

    explicit Poliz(int _size, std::string program = "") {
        size_max = _size;
        lexeme = new Lex[size_max];
        size_cur = 0;
        num_of_ident = 0;
        workspace = std::move(program);
    }

    Lex &operator[](int index);

    static int check(const std::string &buf, std::string *list, int n);

    void put_lex(Lex l) {
        lexeme[size_cur] = std::move(l);
        size_cur++;
    }

    Lex get_lex();
    int get_size_max() const;
    int get_size_cur() const{return size_cur;}
    void incNum(){num_of_ident++;}
    int gc(){
        int a = (int)((unsigned char) workspace[0]);
        workspace.erase(0,1);
        return a;
    }
    static std::string TW[TWlen];
    static std::string TD[TDlen];
    ~Poliz(){
        delete [] lexeme;
    }
};
#endif //MY_CLIENT_POLIZ_H
