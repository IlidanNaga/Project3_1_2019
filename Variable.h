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

    int int_value;
    std::string str_value;
    bool bool_value;

public:

    Variable();
    Variable(const std::string);

    void set_int(const int val);
    void set_str(const std::string val);
    void set_bool(const bool val);

    std::string get_name();
    int get_int();
    std::string get_str();
    bool get_bool();


};