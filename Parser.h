#pragma once

#include "Scanner.h"
#include "Variable.h"
#include <vector>
#include <stack>

/*
 * parser is about syntaxis + semantic analyzis + saving ingredients for POLIZ
 * syntaxis - checking for grammatics via recursive lowerage
 * semantic - checking for logic implementation
*/

/*
 * Как работает полиз:
 * встречаем операнд - кидаем в стек (ссылку или значение)
 * встречаем оператор - кидаем в другой стек
 * встречаем закрывающую скобку - все операнды из второго стека до открывающей
 * скидываем в первый, открывающую удаляем
 *
 */

class Parser {
private:

    Lex curr_lex;
    type_of_lex curr_type;
    int curr_val;

    void get_lex();
    int iter;


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

    void L0();
    void L1();
    void L2();
    void L3();
    void L4();

    void T();

    void F();

    void  check_id();              //checking if identificator (variable) exists in expressinos
    void  check_op();              //checking operation build (is it right)
    void  check_not();             //checking if not is useable
    void  eq_type();               //type equality, must be improved for boolean aswell
    void  eq_bool();               //boolean expression check
    void  check_id_in_read();      //identificator in read checker

    void declare(int, type_of_lex);//declaration of lexemes

public:
    Scanner reader;

    std::vector<int> st_int, st_str, st_bool; //vectors consisting id numbers for each type of variables
    std::vector<int> st_var; //vector containing id numbers of all of the variables
    std::stack<type_of_lex> st_lex;

    std::vector <Lex> poliz;  //vector for poliz, first part of it

    void analyzis();
    void set_file(char * file_name);

    Parser();
    Parser(char * file_name);
};
