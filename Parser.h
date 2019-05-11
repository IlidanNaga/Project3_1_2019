#pragma once

#include "Scanner.h"
#include "Variable.h"
#include <vector>

/*
 * parser is about saving different lexemes into a tables
*/

class Parser {
private:

    Lex curr_lex;
    type_of_lex curr_type;

    void get_lex();
    int iter;

    int max_ident;

    void Start();
    void A();

    void V();

    void I();
    void I1();
    void I2();
    void I3();

    void S();
    void S1();
    void S2();

    void B();
    void B1();
    void B2();
    void B3();

    void C();


public:
    Scanner reader;

    Parser(char * file_name);
};
