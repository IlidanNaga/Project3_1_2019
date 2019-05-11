#pragma once

#include <iostream>
#include <string>
#include "Lex.h"
/*
 * variable is declaration of hardcore lexeme version - variable with different data
 * it'll be
 * integer
 * string
 * boolean
 */


class Variable {
    std::string name;
    type_of_lex type;

    bool declare;
    bool assign;

    int value;


public:

    Variable();
    Variable(const std::string);

    std::string get_name();

    void put_value(int);
    int get_value();

    void put_type(type_of_lex);
    type_of_lex get_type();

    void put_declare();
    bool get_declare() const;

    void put_assign();
    bool get_assign() const;


};