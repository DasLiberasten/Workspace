#ifndef _DATABASE_H_
#define _DATABASE_H_

#define MAX_FIELD_NAME_LEN 15
#define MAX_CELL_SIZE 50
#define MAX_TABLE_NAME_LEN 15
#define MAX_TEXT_LEN 20

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include "Sock_serv.h"


enum field_type {
    NONE,
    TEXT,
    LONG
};
typedef union field_content {
    size_t num;
    char text[MAX_TEXT_LEN];
} field_content;

struct field_struct {
    std::size_t id;
    std::size_t row_pos;
    field_type type;
    field_content field;
};

struct name_struct {
    size_t cell_size;
    field_type type;
    int len;
    std::size_t id;
    std::string name;
};
struct table_struct {
    char table_name[MAX_TABLE_NAME_LEN];
    std::size_t num_of_rows;
    std::size_t num_of_records;
    std::size_t num_nonempty;
};

enum table_exception_code {
    ERR_FILEOPEN,
    ERR_FILEWRITE,
    ERR_FILEREAD,
    ERR_FILESEEK,
    ERR_EMPTYFILE,
    ERR_FILEREMOVE,
    ERR_FILERENAME,
    ERR_FIELDNAME,
    ERR_FIELDLEN,
    ERR_FILENAME,
    ERR_CELLLEN,
    ERR_BASERANGE,
    ERR_TYPE,
    ERR_NAMEEXISTS
};

class TableException {
public:
    std::string err_message;

    explicit TableException(table_exception_code);

    void report(BaseSocket *) const;

    ~TableException() = default;
};

class TableClass {
public:
    table_struct t_struct;
    std::vector<name_struct> field_names;
    std::vector<field_struct> fields;

    TableClass();

    ~TableClass();
};

class Table : public TableClass {
public:
    Table() = default;

    void add_string(const std::string &, const char *, size_t);

    void add_long(const std::string &, size_t, size_t);

    void create_table(const std::string &, std::size_t, std::size_t);

    void open_table(const std::string &);

    void save_table(const std::string &);

    void delete_table(const std::string &);

    void close_table(const std::string &);

    void add_record(const std::string &, field_type, size_t);

    field_type find_record(const std::string &);

    void add_row();

    void delete_row(size_t);

    std::string get_field(const std::string &, std::size_t);

    ~ Table() = default;
};

#endif
