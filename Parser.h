#pragma once

#include "Scanner.h"
#include "Variable.h"
#include <vector>
#include <stack>

/*
 * parser is about saving different lexemes into a tables
*/

class Parser {
private:

    Lex curr_lex;
    type_of_lex curr_type;
    int curr_val;

    void get_lex();
    int iter;

    int max_ident;

    void analyzis();

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
    void D();

    void E0();
    void E1();
    void E2();
    void E3();
    void E4();

    void T();
    void T1();

    void F();
    void F1();


public:
    Scanner reader;

    std::stack<int> st_int, st_str, st_bool;
    std::stack<type_of_lex> st_lex;

    Parser(char * file_name);
};
