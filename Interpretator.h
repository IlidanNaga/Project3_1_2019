#pragma once

#include "Parser.h"


class Interpretator {
private:
    Parser parser;
    Lex pc_el;
public:
    Interpretator(char * file_name);
    void launch();
    void execute(std::vector<Lex> &);
};