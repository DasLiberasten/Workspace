#include "Executor.h"
#include "Database.h"

template <typename T, typename T_EL>
void from_st(T& t, T_EL & x){
    x = t.top();
    t.pop();
}

void Interpretator::expr(Poliz& poliz, std::size_t row){
    Lex local_pol;
    string buf_1, buf_2, buf;
    long i, j;
    int exp_size = poliz.get_size_cur(), index = 0;
        while(index < exp_size){
            local_pol = poliz[index];
            switch(local_pol.get_type()){
                case LEX_NUM:
                    int_args.push(local_pol.get_id());
                    break;
                case LEX_LETTER:
                    str_args.push(local_pol.get_name());
                    break;
                case LEX_NULL:
                    break;
                case LEX_ID:{
                    i = local_pol.get_id();

                    if((table.find_record(local_pol.get_name()) == TEXT)){
                        buf = table.get_field(local_pol.get_name(),row+1);
                        str_args.push(buf);
                    }else{
                        j = stol(table.get_field(local_pol.get_name(),row+1), nullptr,10);
                        int_args.push(j);
                    }
                    break;
                }
                case LEX_NOT:
                    from_st(int_args, i);
                    int_args.push(!i);
                    break;
                case LEX_OR:
                    from_st(int_args, i);
                    from_st(int_args, j);
                    int_args.push(i || j);
                    break;
                case LEX_AND:
                    from_st(int_args, i);
                    from_st(int_args, j);
                    int_args.push(i && j);
                    break;
                case LEX_PLUS:
                    from_st(int_args, i);
                    from_st(int_args, j);
                    int_args.push(i + j);
                    break;
                case LEX_TIMES:
                    from_st(int_args, i);
                    from_st(int_args, j);
                    int_args.push (i * j);
                    break;
                case LEX_MINUS:
                    from_st(int_args, i);
                    from_st(int_args, j);
                    int_args.push(j - i);
                    break;
                case LEX_SLASH:
                    from_st(int_args, i);
                    from_st(int_args, j);
                    if(i){
                        int_args.push (j / i);
                        break;
                    }
                    else throw "poliz: division by zero";
                case LEX_MOD:
                    from_st(int_args, i);
                    from_st(int_args, j);
                    if(i){
                        int_args.push(j % i);
                        break;
                    }
                    else throw "poliz: division by zero";
                case LEX_EQ:
                    if(str_args.empty()){
                        from_st(int_args, i);
                        from_st(int_args, j);
                        int_args.push(i == j);
                    }else{
                        from_st(str_args, buf_1);
                        from_st(str_args, buf_2);
                        int_args.push(buf_1 == buf_2);
                    }
                    break;
                case LEX_GEQ:
                    if(str_args.empty()){
                        from_st(int_args, i);
                        from_st(int_args, j);
                        int_args.push(j >= i);
                    }else{
                        from_st(str_args, buf_1);
                        from_st(str_args, buf_2);
                        int_args.push(buf_2 >= buf_1);
                    }
                    break;
                case LEX_LEQ:
                    if(str_args.empty()){
                        from_st(int_args, i);
                        from_st(int_args, j);
                        int_args.push(j <= i);
                    }else{
                        from_st(str_args, buf_1);
                        from_st(str_args, buf_2);
                        int_args.push(buf_2 <= buf_1);
                    }
                    break;
                case LEX_LSS:
                    if(str_args.empty()){
                        from_st(int_args, i);
                        from_st(int_args, j);
                        int_args.push(j < i);
                    }else{
                        from_st(str_args, buf_1);
                        from_st(str_args, buf_2);
                        int_args.push(buf_2 < buf_1);
                    }
                    break;
                case LEX_GTR:
                    if(str_args.empty()){
                        from_st(int_args, i);
                        from_st(int_args, j);
                        int_args.push(j > i);
                    }
                    else{
                        from_st(str_args, buf_1);
                        from_st(str_args, buf_2);
                        int_args.push (buf_2 > buf_1);
                    }
                    break;
                case LEX_NEQ:
                    if(str_args.empty()){
                        from_st(int_args, i);
                        from_st(int_args, j);
                        int_args.push(j != i);
                    }else{
                        from_st(str_args, buf_1);
                        from_st(str_args, buf_2);
                        int_args.push(buf_2 != buf_1);
                    }
                    break;
                default:
                    throw 0;
            }
            ++index;
        }
}

vector<bool> Interpretator::where(){
    vector<bool> res; // вектор хороших колонок
    long t;
    gp();
    Poliz exp(1000);
    if(current.get_type() == LEX_ALL){
        for (size_t i = 0; i<table.t_struct.num_of_rows;i++)
            res.push_back(true);
        gp();
    }
    else{
        while((current.get_type() != POLIZ_SENTENCE) && (current.get_type() != LEX_IN) && (current.get_type() != LEX_NOT)){
            exp.put_lex(current);
            gp();
        }
        if(current.get_type() != POLIZ_SENTENCE){
            int flag = 0;
            if(current.get_type() == LEX_NOT){
                flag = 1;
                gp();
            }
            gp();

            if(current.get_type() == LEX_NUM){
                vector<int> constants;
                long l;
                while(current.get_type() != POLIZ_SENTENCE){
                    constants.push_back(current.get_id());
                    gp();
                }
                for (size_t i = 0; i<table.t_struct.num_of_rows;i++){
                    bool q = flag;
                    expr(exp, i);
                    from_st(int_args, l);
                        for(int constant : constants){
                            if(l == constant){
                                q = !q;
                                break;
                            }
                        }
                    res.push_back(q);
                }
            }
            else{
                vector<string> constants;
                string str;
                while(current.get_type() != POLIZ_SENTENCE){
                    constants.push_back(current.get_name());
                    gp();
                }
                for (size_t i = 0; i<table.t_struct.num_of_rows;i++){
                    expr(exp, i);
                    from_st(str_args, str);
                    for(auto & constant : constants){
                            if(str == constant){
                                flag = !flag;
                                break;
                            }
                        }
                    res.push_back(flag);
                }
            }
        }
        else{
            for (size_t i = 0; i<table.t_struct.num_of_rows;i++){
                expr(exp, i);
                from_st(int_args, t);
                res.push_back(t);
            }
        }
    }
    return res;
}

void Interpretator::execute(){
    current = p.poliz[id];
        while (id < size) {
            switch (current.get_type()) {
                case LEX_CREATE: {
                    gp();
                    name = current.get_name();
                    table.create_table(name, 0, 0);
                    gp();
                    while (current.get_type() != POLIZ_SENTENCE) {
                        string temp = current.get_name();
                        gp();
                        if (current.get_type() == LEX_TEXT) {
                            gp();
                            table.add_record(temp, TEXT, current.get_id());
                        }
                        else table.add_record(temp,LONG, 0);
                        gp();
                    }
                    table.save_table(name);
                    table.close_table(name);
                    break;
                }
                case LEX_DROP: {
                    gp();
                    name = current.get_name();
                    table.delete_table(name);
                    gp();
                    break;
                }
                case LEX_INSERT: {
                    gp();
                    name = current.get_name();
                    table.open_table(name);
                    std::size_t len = table.t_struct.num_of_records;
                    vector<string> fieldNames;
                    gp();
                    table.add_row();
                    for (std::size_t k = 0; k < len; k++) {
                        if ((current.get_type() == LEX_LETTER) || (current.get_type() == LEX_TEXT))
                            table.add_string(table.field_names[k].name, current.get_name().c_str(), table.t_struct.num_of_rows);
                        else
                            table.add_long(table.field_names[k].name, current.get_id(), table.t_struct.num_of_rows);
                        gp();
                    }
                    table.save_table(name);
                    table.close_table(name);
                    break;
                }
                case LEX_DELETE: {
                    int k = 0;
                    gp();
                    name = current.get_name();
                    table.open_table(name);
                    gp();
                    vector<bool> wh = where();
                    for (std::size_t i = 0; i < wh.size(); i++) {
                        if (wh[i]) {
                            table.delete_row(i - k);
                            k++;
                        }
                    }
                    table.save_table(name);
                    table.close_table(name);
                    break;
                }
                case LEX_UPDATE: {
                    gp();
                    name = current.get_name();
                    table.open_table(name);
                    gp();
                    string active_column = current.get_name();
                    Lex_type column_type;
                    if (table.find_record(current.get_name()) == TEXT)
                        column_type = LEX_TEXT;
                    else column_type = LEX_NUM;
                    gp();
                    Poliz assign_exp(1000);
                    while (current.get_type() != LEX_WHERE) {
                        assign_exp.put_lex(current);
                        gp();
                    }
                    vector<bool> wh = where();
                    for (std::size_t i = 0; i < table.t_struct.num_of_rows; i++) {
                        if (wh[i]) {
                            expr(assign_exp, i);
                            if (column_type == LEX_TEXT) {
                                string buf;
                                from_st(str_args, buf);
                                table.add_string(active_column,buf.c_str(),i+1);
                            } else {
                                long buf;
                                from_st(int_args, buf);
                                table.add_long(active_column,buf,i+1);
                            }
                        }
                    }
                    table.save_table(name);
                    table.close_table(name);
                    break;
                }
                case LEX_SELECT: {
                    bool all = false;
                    vector<string> columns;
                    gp();
                    if (current.get_type() == LEX_ALLCOLS) {
                        all = true;
                        gp();
                    }
                    else {
                        while (current.get_type() != LEX_FROM) {
                            columns.push_back(current.get_name());
                            gp();
                        }
                    }
                    gp();
                    name = current.get_name();
                    table.open_table(name);

                    if (all) {
                        for (std::size_t i = 0; i < table.t_struct.num_of_records; i++)
                            columns.push_back(table.field_names[i].name);
                    }

                    gp();
                    vector<bool> wh = where();
                    char buf[MAX_CELL_SIZE];
                    char buf1[100000];
                    memset(buf1,0,100000);
                    for (auto & column : columns) {
                        memset(buf, 0, MAX_CELL_SIZE);
                        sprintf(buf, "|%20s", column.c_str());
                        strcat(buf1,buf);
                    }
                    strcat(buf1,"\n");
                    for (size_t j=0; j<wh.size(); j++) {
                        if (!wh[j])
                            continue;
                        for (auto & column : columns) {
                            memset(buf, 0, MAX_CELL_SIZE);
                            sprintf(buf, "|%20s", table.get_field(column,j+1).c_str());
                            strcat(buf1,buf);
                        }
                        strcat(buf1,"\n");
                    }
                    strcat(buf1,"\n;");
                    pSocket->putString(buf1);
                    vivod = true;
                    table.save_table(name);
                    table.close_table(name);
                    break;
                }
                default: throw 1;
            }
            gp();
        }
}