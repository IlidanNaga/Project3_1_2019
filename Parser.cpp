#include "Parser.h"

Parser::Parser(char * file_name) {
    reader.set_file(file_name);
    reader.build_table();
    std::cout << std::endl;
    iter = 0;
    max_ident = -1;
    analyzis();
}

void Parser::analyzis() {
    Start();
    if (curr_type != LEX_FIN)
        throw curr_lex;
    std::cout << "First part of syntaxis analyzis completed" << std::endl;
}

void Parser::get_lex() {
    curr_lex = reader.Lex_table[iter];
    curr_type = curr_lex.show_type();
    curr_val = curr_lex.show_value();
    iter ++;
    if (iter > reader.Lex_table.size())
        throw "Out of Lex table's bounds";
}

void Parser::Start() {
    get_lex();
    if (curr_type == LEX_PROGRAM) {
        get_lex();
        A();
        C();
        if (curr_type == LEX_END)
            get_lex();
        else
            throw curr_lex;
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
}

void Parser::I() {
    if (curr_type == LEX_ID) {
        if (curr_lex.show_value() > max_ident)
            max_ident = curr_lex.show_value();
        st_int.push(curr_val);
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
        st_str.push(curr_val);
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
        st_bool.push(curr_val);
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

void Parser::C() {
    D();
    while (curr_type == LEX_SEMICOLON) {
        get_lex();
        D();
    }
}

void Parser::D() {
    if (curr_type == LEX_READ) {
        get_lex();
        if (curr_type == LEX_LPAREN) {
            get_lex();
            if (curr_type == LEX_ID) {
                get_lex();
            }
            else
                throw curr_lex;

            if (curr_type == LEX_RPAREN){
                get_lex();
            } else
                throw curr_lex;
        }
        else
            throw curr_lex;
    }
    else if (curr_type == LEX_IF) {
        get_lex();
        E0();
        D();
        if (curr_type == LEX_ELSE) {
            get_lex();
            D();
        }
    }
    else if (curr_type == LEX_WHILE) {
        get_lex();
        E0();
        D();
    }
    else if (curr_type == LEX_WRITE) {
        get_lex();
        if (curr_type == LEX_LPAREN) {
            get_lex();
            E0();
            while (curr_type == LEX_COMMA) {
                get_lex();
                E0();
            }
            if (curr_type == LEX_RPAREN) {
                get_lex();
            } else
                throw curr_lex;
        }
    }
    else if (curr_type == LEX_ID) {
        get_lex();
        if (curr_type == LEX_ASSIGN) {
            get_lex();
            E0();
        } else
            throw curr_lex;
    }
    else if (curr_type == LEX_BEGIN) {
        get_lex();
        C();
        if (curr_type == LEX_END) {
            get_lex();
            D();
        } else
            throw curr_lex;
    }
}

void Parser::E0() {
    E1();
    if (curr_type == LEX_ASSIGN) {
        st_lex.push(curr_type);
        get_lex();
        E1();
    }
}

void Parser::E1() {
    E2();
    if (curr_type == LEX_OR) {
        st_lex.push(curr_type);
        get_lex();
        E2();
    }
}

void Parser::E2() {
    E3();
    while (curr_type == LEX_AND) {
        st_lex.push(curr_type);
        get_lex();
        E3();
    }
}

void Parser::E3() {
    E4();
    if (curr_type == LEX_EQ || curr_type == LEX_LSS || curr_type == LEX_GTR ||
        curr_type == LEX_LEQ || curr_type == LEX_GEQ || curr_type == LEX_NEQ) {
        st_lex.push(curr_type);
        get_lex();
        E4();
    }
}

void Parser::E4() {
    T();
    while (curr_type == LEX_PLUS || curr_type == LEX_MINUS) {
        st_lex.push(curr_type);
        get_lex();
        T();
    }
}

void Parser::T() {
    F();
    while (curr_type == LEX_TIMES || curr_type == LEX_SLASH) {
        st_lex.push(curr_type);
        get_lex();
        F();
    }
}

void Parser::F() {
    if (curr_type == LEX_ID) {
        get_lex();
    }
    else if (curr_type == LEX_NUM) {
        st_lex.push(LEX_INT);
        get_lex();
    }
    else if (curr_type == LEX_STRC) {
        st_lex.push(LEX_STRING);
        get_lex();
    }
    else if (curr_type == LEX_NOT) {
        get_lex();
        F();
    }
    else if (curr_type == LEX_LPAREN) {
        get_lex();
        E0();
        if (curr_type == LEX_RPAREN)
            get_lex();
        else
            throw curr_lex;
    }
    else
        throw curr_lex;
}

void Parser::dec ( type_of_lex type ) {
    int i;
    while ( !st_int.empty()) {
        i = st_int.top();
        st_int.pop();
        if ( reader.Var_table[i].get_declare() )
            throw "Variable declared twice";
        else {
            reader.Var_table[i].put_declare();
            reader.Var_table[i].put_type(type);
        }
    }
}

void Parser::check_id () {
    if ( reader.Var_table[curr_val].get_declare() )
        st_lex.push ( reader.Var_table[curr_val].get_type() );
    else
        throw "not declared";
}

void Parser::check_op () {
    type_of_lex t1, t2, op, t = LEX_INT, r = LEX_BOOL;

    t2 = st_lex.top();
    st_lex.pop();
    op = st_lex.top();
    st_lex.pop();
    t1 = st_lex.top();
    st_lex.pop();
    if (op == LEX_PLUS || op == LEX_MINUS || op == LEX_TIMES || op == LEX_SLASH)
        r = LEX_INT;
    if (op == LEX_OR || op == LEX_AND)
        t = LEX_BOOL;
    if (t1 == t2  &&  t1 == t)
        st_lex.push(r);
    else
        throw "wrong types are in operation";
    poliz.push_back (Lex (op) );
}

void Parser::check_not () {
    if (st_lex.top() != LEX_BOOL)
        throw "wrong type is in not";
    else
        poliz.push_back (Lex (LEX_NOT));
}

void Parser::eq_type () {
    type_of_lex t = st_lex.top();
    st_lex.pop();
    if ( t != st_lex.top())
        throw "wrong types are in :=";
    st_lex.pop();
}

void Parser::eq_bool () {
    if ( st_lex.top() != LEX_BOOL )
        throw "expression is not boolean";
    st_lex.pop();
}

void Parser::check_id_in_read () {
    if ( !reader.Var_table [curr_val].get_declare() )
        throw "not declared";
}
