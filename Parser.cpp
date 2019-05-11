#include "Parser.h"

Parser::Parser(char * file_name) {
    reader.set_file(file_name);
    reader.build_table();
    iter = 0;
    max_ident = -1;
    Start();
}

void Parser::get_lex() {
    curr_lex = reader.Lex_table[iter];
    curr_type = curr_lex.show_type();
    iter ++;
    if (iter >= reader.Lex_table.size())
        throw "Out of table's bounds";
}

void Parser::Start() {
    get_lex();
    if (curr_type == LEX_PROGRAM) {
        get_lex();
        A();
    }
    else if (curr_type == LEX_FIN) {

    } else {
        throw curr_lex;
    }
}

void Parser::A() {
    if (curr_type == LEX_BEGIN) {
        get_lex();
        V();
    } else {
        throw curr_lex;
    }

}

void Parser::V() {

    while (curr_type == LEX_INT || curr_type == LEX_STRING || curr_type == LEX_BOOL) {
        if (curr_type == LEX_INT) {
            get_lex();
            I();
        }
        else if (curr_type == LEX_STRING) {
            get_lex();
            S();
        }
        else if (curr_type == LEX_BOOL) {
            get_lex();
            B();
        }
    }
    C();
}

void Parser::I() {
    if (curr_type == LEX_ID) {
        if (curr_lex.show_value() > max_ident)
            max_ident = curr_lex.show_value();

        get_lex();
        I1();
    } else {
        throw curr_lex;
    }
}

void Parser::I1() {
    if (curr_type == LEX_ASSIGN) {
        get_lex();
        I2();
    } else {
        I3();
    }
}

void Parser::I2() {
    if (curr_type == LEX_MINUS || curr_type == LEX_PLUS) {
        get_lex();
        if (curr_type == LEX_NUM) {
            get_lex();
            I3();
        }
    }
    else if (curr_type == LEX_NUM) {
        get_lex();
        I3();
    } else {
        throw curr_lex;
    }
}

void Parser::I3() {
    if (curr_type == LEX_COMMA) {
        get_lex();
        I();
    }
    else if (curr_type == LEX_SEMICOLON) {
        get_lex();
    } else {
        throw curr_lex;
    }
}

void Parser::S() {
    if (curr_type == LEX_ID) {
        if (curr_lex.show_value() > max_ident)
            max_ident = curr_lex.show_value();
        get_lex();
        S1();
    } else {
        throw curr_lex;
    }
}

void Parser::S1() {
    if (curr_type == LEX_ASSIGN) {
        get_lex();
        if (curr_type == LEX_STRC) {
            get_lex();
            S2();
        } else {
            throw curr_lex;
        }
    } else {
        S2();
    }
}

void Parser::S2() {
    if (curr_type == LEX_COMMA) {
        get_lex();
        S();
    }
    else if (curr_type == LEX_SEMICOLON) {
        get_lex();
    } else {
        throw curr_lex;
    }
}

void Parser::B() {
    if (curr_type == LEX_ID) {
        if (curr_lex.show_value() > max_ident)
            max_ident = curr_lex.show_value();
        get_lex();
        B1();
    } else {
        throw curr_lex;
    }
}

void Parser::B1() {
    if (curr_type == LEX_ASSIGN) {
        get_lex();
        B2();
    } else {
        B3();
    }
}

void Parser::B2() {
    if (curr_type == LEX_TRUE || curr_type == LEX_FALSE) {
        get_lex();
        B3();
    } else {
        throw curr_lex;
    }
}

void Parser::B3() {
    if (curr_type == LEX_COMMA) {
        get_lex();
        B();
    }
    else if (curr_type == LEX_SEMICOLON) {
        get_lex();
    } else {
        throw curr_lex;
    }
}
