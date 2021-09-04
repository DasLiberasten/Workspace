#include "Database.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>

TableException::TableException(table_exception_code errcode) {
    switch (errcode) {
        case ERR_FILEOPEN:
            err_message = "Can't open file";
            break;
        case ERR_FILEWRITE:
            err_message = "Can't write to file";
            break;
        case ERR_FILEREAD:
            err_message = "Can't read from file";
            break;
        case ERR_FILESEEK:
            err_message = "Can't move the pointer";
            break;
        case ERR_EMPTYFILE:
            err_message = "File you try to open is empty";
            break;
        case ERR_FILEREMOVE:
            err_message = "Can't delete file;";
            break;
        case ERR_FILERENAME:
            err_message = "Can't rename file;";
            break;
        case ERR_FIELDNAME:
            err_message = "No such field name;";
            break;
        case ERR_FIELDLEN:
            err_message = "Wrong field name or string length;";
            break;
        case ERR_FILENAME:
            err_message = "Wrong table name length;";
            break;
        case ERR_CELLLEN:
            err_message = "Wrong cell name length;";
            break;
        case ERR_BASERANGE:
            err_message = "Index is out of range;";
            break;
        case ERR_TYPE:
            err_message = "Wrong field type;";
            break;
        case ERR_NAMEEXISTS:
            err_message = "Name already exists;";
            break;
        default:
            break;
    }
}

void TableException::report(BaseSocket *sock) const {
    sock->putString(err_message);
}

TableClass::TableClass() {
    t_struct.num_of_rows = 0;
    t_struct.num_of_records = 0;
    t_struct.num_nonempty = sizeof(struct table_struct);
}

TableClass::~TableClass() {
    field_names.clear();
    fields.clear();
}

void Table::create_table(const std::string &t_name, size_t rec, size_t row) {
    if (t_name.length() > MAX_TABLE_NAME_LEN)
        throw TableException(ERR_FILENAME);
    FILE *f = fopen(t_name.c_str(), "wb+");
    if (f == nullptr)
        throw TableException(ERR_FILEOPEN);
    strcpy(t_struct.table_name, t_name.c_str());
    t_struct.num_of_records = rec;
    t_struct.num_of_rows = row;
    t_struct.num_nonempty = 0;
    if (fwrite(&(t_struct), sizeof(struct table_struct), 1, f) == 0)
        throw TableException(ERR_FILEWRITE);
    for (size_t i = 0; i < rec; i++) {
        name_struct buf;
        buf.name = std::to_string(i);
        buf.len = buf.name.length();
        buf.type = NONE;
        while (true) {
            std::size_t a = rand();
            auto itt = field_names.begin();
            while (itt != field_names.end()) {
                if (a == (*itt).id) {
                    break;
                }
                itt++;
            }
            if (itt == field_names.end()) {
                buf.id = a;
                break;
            }
        }
        field_names.push_back(buf);
        if (fwrite(&(buf.id), sizeof(buf.id), 1, f) == 0)
            throw TableException(ERR_FILEWRITE);
        if (fwrite(&(buf.len), sizeof(buf.len), 1, f) == 0)
            throw TableException(ERR_FILEWRITE);
        if (fwrite(&(buf.type), sizeof(buf.type), 1, f) == 0)
            throw TableException(ERR_FILEWRITE);
        if (fwrite(&(buf.cell_size), sizeof(buf.cell_size), 1, f) == 0)
            throw TableException(ERR_FILEWRITE);
        const char *str = buf.name.c_str();
        if (fwrite(str, buf.name.length(), 1, f) == 0)
            throw TableException(ERR_FILEWRITE);
    }
    fclose(f);
}

void Table::open_table(const std::string &t_name) {
    {
        FILE *f = fopen(t_name.c_str(), "rb");
        if (f == nullptr)
            throw TableException(ERR_FILEOPEN);
        if (fseek(f, 0, SEEK_SET) != 0)
            throw TableException(ERR_FILESEEK);
        if (feof(f))
            throw TableException(ERR_EMPTYFILE);

        if (fread(&(t_struct), sizeof(struct table_struct), 1, f) == 0) {
            throw TableException(ERR_FILEREAD);
        }
        for (size_t i = 0; i < t_struct.num_of_records; i++) {
            name_struct buf;
            if (fread(&(buf.id), sizeof(size_t), 1, f) == 0)
                throw TableException(ERR_FILEREAD);
            if (fread(&(buf.len), sizeof(int), 1, f) == 0)
                throw TableException(ERR_FILEREAD);
            if (fread(&(buf.type), sizeof(buf.type), 1, f) == 0)
                throw TableException(ERR_FILEREAD);
            if (fread(&(buf.cell_size), sizeof(buf.cell_size), 1, f) == 0)
                throw TableException(ERR_FILEREAD);
            char *str = new char[buf.len + 1];
            memset(str, 0, buf.len + 1);
            if (fread(str, buf.len, 1, f) == 0) {
                throw TableException(ERR_FILEREAD);
            }
            buf.name = std::string(str);
            field_names.push_back(buf);
            delete[] str;
        }
        for (size_t i = 0; i < t_struct.num_nonempty; i++) {
            struct field_struct f_struct;
            if (fread(&(f_struct), sizeof(f_struct), 1, f) == 0) {
                throw TableException(ERR_FILEREAD);
            }
            fields.push_back(f_struct);
        }
        fclose(f);
    }
}

void Table::save_table(const std::string &t_name) {
    if (t_name.length() > MAX_TABLE_NAME_LEN)
        throw TableException(ERR_FILENAME);
    FILE *f = fopen(t_name.c_str(), "wb+");
    if (f == nullptr)
        throw TableException(ERR_FILEOPEN);

    if (fwrite(&(t_struct), sizeof(struct table_struct), 1, f) == 0) {
        throw TableException(ERR_FILEWRITE);
    }
    for (size_t i = 0; i < t_struct.num_of_records; i++) {
        if (fwrite(&(field_names[i].id), sizeof(field_names[i].id), 1, f) == 0)
            throw TableException(ERR_FILEWRITE);
        if (fwrite(&(field_names[i].len), sizeof(field_names[i].len), 1, f) == 0)
            throw TableException(ERR_FILEWRITE);
        if (fwrite(&(field_names[i].type), sizeof(field_names[i].type), 1, f) == 0)
            throw TableException(ERR_FILEWRITE);
        if (fwrite(&(field_names[i].cell_size), sizeof(field_names[i].cell_size), 1, f) == 0)
            throw TableException(ERR_FILEWRITE);
        const char *str = field_names[i].name.c_str();
        if (fwrite(str, field_names[i].name.length(), 1, f) == 0)
            throw TableException(ERR_FILEWRITE);
    }
    for (size_t i = 0; i < t_struct.num_nonempty; i++) {
        if (fwrite(&(fields[i]), sizeof(fields[i]), 1, f) == 0)
            throw TableException(ERR_FILEWRITE);
    }
    fclose(f);
}

void Table::add_string(const std::string &name, const char *content, size_t row) {
    if (strlen(content) > MAX_TEXT_LEN)
        throw TableException(ERR_CELLLEN);
    if (t_struct.num_of_rows < row)
        throw TableException(ERR_BASERANGE);
    field_struct buf;
    auto itt = field_names.begin();
    while (itt != field_names.end()) {
        if (name == (*itt).name) {
            if ((*itt).type != TEXT)
                throw TableException(ERR_TYPE);
            if (strlen(content) > (*itt).cell_size)
                throw TableException(ERR_CELLLEN);
            buf.id = (*itt).id;
            break;
        }
        itt++;
    }
    if (itt == field_names.end())
        throw TableException(ERR_FIELDNAME);
    auto itt1 = fields.begin();
    while (itt1 != fields.end()) {
        if ((*itt1).id == buf.id && (*itt1).row_pos == row) {
            strcpy(buf.field.text, content);
            return;
        }
        itt1++;
    }
    buf.type = TEXT;
    strcpy(buf.field.text, content);
    buf.row_pos = row;
    fields.push_back(buf);
    t_struct.num_nonempty++;
}

void Table::add_long(const std::string &name, size_t content, size_t row) {
    if (t_struct.num_of_rows < row)
        throw TableException(ERR_BASERANGE);
    field_struct buf;
    auto itt = field_names.begin();
    while (itt != field_names.end()) {
        if (name == (*itt).name) {
            if ((*itt).type != LONG)
                throw TableException(ERR_TYPE);
            buf.id = (*itt).id;
            break;
        }
        itt++;
    }
    if (itt == field_names.end())
        throw TableException(ERR_FIELDNAME);

    auto itt1 = fields.begin();
    while (itt1 != fields.end()) {
        if ((*itt1).id == buf.id && (*itt1).row_pos == row) {
            (*itt1).field.num = content;
            return;
        }
        itt1++;
    }
    buf.type = LONG;
    buf.field.num = content;
    buf.row_pos = row;
    fields.push_back(buf);
    t_struct.num_nonempty++;
}

void Table::delete_table(const std::string &t_name) {
    t_struct.num_of_records = 0;
    t_struct.num_nonempty = 0;
    t_struct.num_of_rows = 0;
    memset(t_struct.table_name, 0, MAX_TABLE_NAME_LEN);
    field_names.clear();
    fields.clear();
    if (remove(t_name.c_str()) != 0)
        throw TableException(ERR_FILEREMOVE);
}


void Table::close_table(const std::string &t_name) {
    t_struct.num_of_records = 0;
    t_struct.num_nonempty = 0;
    t_struct.num_of_rows = 0;
    memset(t_struct.table_name, 0, MAX_TABLE_NAME_LEN);
    field_names.clear();
    fields.clear();
}

void Table::add_record(const std::string &name, field_type type, size_t size) {
    auto itt = field_names.begin();
    while (itt != field_names.end()) {
        if ((*itt).name == name) {
            throw TableException(ERR_NAMEEXISTS);
        }
        itt++;
    }
    if (name.length() > MAX_FIELD_NAME_LEN)
        throw TableException(ERR_FIELDLEN);
    name_struct a;
    a.name = name;
    a.type = type;
    a.len = name.length();
    while (true) {
        std::size_t k = rand();
        auto itt1 = field_names.begin();
        while (itt1 != field_names.end()) {
            if (k == (*itt1).id) {
                break;
            }
            itt1++;
        }
        if (itt1 == field_names.end()) {
            a.id = k;
            break;
        }
    }
    if (size > MAX_CELL_SIZE)
        throw TableException(ERR_FIELDLEN);
    a.cell_size = size;
    field_names.push_back(a);
    t_struct.num_of_records++;
}

void Table::add_row() {
    t_struct.num_of_rows++;
}

void Table::delete_row(size_t row) {
    if (row > t_struct.num_of_rows)
        throw TableException(ERR_BASERANGE);
    auto itt = fields.begin();
    while (itt != fields.end()) {
        if ((*itt).row_pos > row)
            (*itt).row_pos--;
        if ((*itt).row_pos == row) {
            itt--;
            fields.erase(itt + 1);
            t_struct.num_nonempty--;
        }
        itt++;
    }
    t_struct.num_of_rows--;
}

std::string Table::get_field(const std::string &name, std::size_t row) {
    std::string buf;
    auto itt = field_names.begin();
    while (itt != field_names.end()) {
        if ((*itt).name == name)
            break;
        itt++;
    }
    if (itt == field_names.end())
        throw TableException(ERR_FIELDNAME);
    auto itt1 = fields.begin();
    while (itt1 != fields.end()) {
        if ((*itt1).id == (*itt).id && (*itt1).row_pos == row) {
            if ((*itt1).type == NONE)
                buf = " ";
            if ((*itt1).type == TEXT)
                buf = (*itt1).field.text;
            if ((*itt1).type == LONG)
                buf = std::to_string((*itt1).field.num);
            return buf;
        }
        itt1++;
    }
    buf = " ";
    return buf;
}

field_type Table::find_record(const std::string &_name) {
    auto itt = field_names.begin();
    while (itt != field_names.end()) {
        if ((*itt).name == _name)
            return (*itt).type;
        itt++;
    }
    return NONE;
}
