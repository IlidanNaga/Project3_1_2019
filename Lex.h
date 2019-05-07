#pragma once

#include <iostream>

/*
 * what lex is meant to do - just to implement a Lexeme type
 */

enum type_of_lex {
    Lex_Null,
    Lex_Program, Lex_LFB, Lex_RFB, Lex_Int, Lex_String,
    Lex_Assign, Lex_Comma, Lex_Number, Lex_Word, Lex_Semicolon,
    Lex_Plus, Lex_Minus, Lex_Not, Lex_And, Lex_Or,
    Lex_Multiply, Lex_Divide, Lex_Bigger, Lex_Less, Lex_Equal,
    Lex_BE, Lex_LE, Lex_NE, Lex_LB, Lex_RB,
    Lex_If, Lex_else, Lex_While, Lex_Read, Lex_Write
};

class Lex {
private:
    type_of_lex Lex_type;
public:
    Lex();
    Lex(class Lex &);

    type_of_lex show_type();

};