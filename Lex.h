#pragma once

#include <iostream>
#include <fstream>

/*
 * what lex is meant to do - just to implement a Lexeme type
 */

enum type_of_lex {
    LEX_NULL, LEX_AND, LEX_BEGIN, LEX_BOOL, LEX_DO, LEX_ELSE, LEX_END, LEX_IF, LEX_FALSE, LEX_INT,
    LEX_STRING, LEX_NOT, LEX_OR, LEX_PROGRAM, LEX_READ, LEX_TRUE, LEX_WHILE, LEX_WRITE,
    LEX_FIN, LEX_SEMICOLON, LEX_COMMA, LEX_COLON, LEX_ASSIGN, LEX_LPAREN, LEX_RPAREN, LEX_EQ,
    LEX_LSS, LEX_GTR, LEX_PLUS, LEX_MINUS, LEX_TIMES, LEX_SLASH, LEX_LEQ, LEX_NEQ, LEX_GEQ,
    LEX_NUM, LEX_STRC, LEX_ID, POLIZ_LABEL, POLIZ_ADDRESS, POLIZ_GO, POLIZ_FGO
};


class Lex {
private:
    type_of_lex Lex_type;
    int value;
public:
    Lex(type_of_lex t = LEX_NULL, int v = 0): Lex_type(t), value(v) {}
    type_of_lex show_type();
    int show_value();

    friend std::ostream& operator<<(std::ostream&, Lex);

};