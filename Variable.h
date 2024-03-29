#pragma once

#include <iostream>
#include <string>
#include "Lex.h"
/*
 * variable is declaration of hardcore lexeme version - variable with data pole
 * for integer variable it'd be just it's value
 * for boolean - 1 - true, 0 - false
 * for string - index of it's value into strings' vector
 */


class Variable {
    std::string name;
    type_of_lex type;

    bool declare;
    bool assign;

    int value;
    std::string str_value;


public:

    Variable();
    Variable(const std::string);

    std::string get_name();

    void put_value(int);
    int get_value();

    void put_string(std::string);
    std::string get_string();

    void put_type(type_of_lex);
    type_of_lex get_type();

    void put_declare();
    bool get_declare() const;

    void put_assign();
    bool get_assign() const;


};