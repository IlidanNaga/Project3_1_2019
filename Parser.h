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

    void  dec ( type_of_lex type);  //checking is variable is declared just once;
    void  check_id ();              //checking if identificator (variable) exists in expressinos
    void  check_op ();              //checking operation build (is it right)
    void  check_not ();             //checking if not is useable
    void  eq_type ();               //type equality, must be improved for boolean aswell
    void  eq_bool ();               //boolean expression check
    void  check_id_in_read ();      //identificator in read checker

public:
    Scanner reader;

    std::stack<int> st_int, st_str, st_bool;
    std::stack<type_of_lex> st_lex;
    std::vector <Lex> poliz;

    Parser(char * file_name);
};
