#pragma once

#include "Lex.h"
#include <vector>


/*
 * what scanner is meant to do - it has to load new lex from file via getlex
 */


class Scanner {
private:

    FILE *fin;
    char buff;

    void get_char();
    void unget_char(char c);

public:

    Scanner(char * file_name);

    Lex get_lex();

};