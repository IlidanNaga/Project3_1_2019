#pragma once

#include "Lex.h"
#include "Variable.h"
#include <vector>
#include <algorithm>


/*
 * what scanner is meant to do - it has to load new lex from file via getlex and put it into a table
 */


class Scanner {
private:

    enum state {Start, Var, Str, Numb, Comment, Logic, Corner_state};

    static const char *TW[], *TD[];

    FILE *fin;
    char buff;

    void get_char();
    void unget_char(char c);

    int look(const std::string &buf, const char **list);
    int put_var(const std::string &);
    int put_str(const std::string &);

public:

    std::vector<Lex> Lex_table;
    std::vector<Variable> Var_table;
    std::vector<std::string> Str_table;

    Scanner() {}
    Scanner(char *);

    void set_file(char * file_name);

    Lex get_lex();
    void build_table();
};