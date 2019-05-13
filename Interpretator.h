#pragma once

#include "Parser.h"

/*
 * Как работает полиз:
 * встречаем операнд - кидаем в стек (ссылку или значение)
 * встречаем оператор - кидаем в другой стек
 * встречаем закрывающую скобку - все операнды из второго стека до открывающей
 * скидываем в первый, открывающую удаляем
 *
 */


class Interpretator {
private:
    Parser parser;
    Lex pc_el;

    void print_stack(std::stack<Variable> &);
public:

    std::vector<std::string> TS;
    std::vector<Variable> TID;

    int put_TS(const std::string &);

    Interpretator(char * file_name);
    void launch();
    void execute(std::vector<Lex> &);
};