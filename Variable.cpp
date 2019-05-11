#include "Variable.h"

Variable::Variable() {
    declare = false;
    assign = false;
    type = LEX_NULL;
}

Variable::Variable(const std::string s) {
    name = s;
    declare = false;
    assign = false;
    type = LEX_NULL;
}

void Variable::put_declare() {
    declare = true;
}

bool Variable::get_declare() const {
    return declare;
}

void Variable::put_assign() {
    assign = true;
}

bool Variable::get_assign() const {
    return assign;
}


std::string Variable::get_name() {
    return name;
}

int Variable::get_value() {
    return value;
}

type_of_lex Variable::get_type() {
    return type;
}

void Variable::put_value(int i) {
    value = i;
}

void Variable::put_type(type_of_lex t) {
    type = t;
}