#pragma once

#include "Parser.h"

/*
 * Interpretation from POLIZ
 */


class Interpretator {
private:
    Parser parser;
    Lex pc_el;

    void print_stack(std::stack<Variable> &);
public:

    std::vector<std::string> TS;
    std::vector<Variable> TID;

    int put_TS(const std::string &);

    Interpretator(char * file_name);
    void launch();
    void execute(std::vector<Lex> &);
};