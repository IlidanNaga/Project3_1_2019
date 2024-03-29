#include "Parser.h"

Parser::Parser() {
    iter = 0;
}

void Parser::set_file(char * file_name) {
    reader.set_file(file_name);
    reader.build_table();
    std::cout << std::endl;
}

Parser::Parser(char * file_name) {
    reader.set_file(file_name);
    reader.build_table();
    std::cout << std::endl;
    iter = 0;
    analyzis();
}

void Parser::analyzis() {
    Start();
    if (curr_type != LEX_FIN)
        throw curr_lex;
    std::cout << "Part of syntaxis + semantic analyzis completed" << std::endl;
    for (int i = 0; i < poliz.size(); i++) {
        std::cout << poliz[i];
    }
    std::cout << std::endl;
}

void Parser::get_lex() {
    curr_lex = reader.Lex_table[iter];
    curr_type = curr_lex.show_type();
    curr_val = curr_lex.show_value();
    iter ++;
    if (iter > reader.Lex_table.size())
        throw "Out of Lex table's bounds";
}
//init
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
//redundant
void Parser::A() {
    if (curr_type == LEX_BEGIN) {
        get_lex();
        V();
    } else {
        throw curr_lex;
    }

}
//variable
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
//int
void Parser::I() {
    if (curr_type == LEX_ID) {
        declare(curr_val, LEX_INT);
        poliz.push_back(Lex(POLIZ_ADDRESS, curr_val));
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
        poliz.pop_back();
        I3();
    }
}
void Parser::I2() {
    if (curr_type == LEX_MINUS) {
        get_lex();
        if (curr_type == LEX_NUM) {
            poliz.push_back(curr_lex);
            poliz.push_back(Lex(LEX_ASSIGN));
            get_lex();
            I3();
        } else
            throw curr_lex;
        poliz.push_back(Lex(LEX_UN_MINUS));
    }
    else if (curr_type == LEX_PLUS) {
        get_lex();
        if (curr_type == LEX_NUM) {
            poliz.push_back(curr_lex);
            poliz.push_back(Lex(LEX_ASSIGN));
            get_lex();
            I3();
        } else
            throw curr_lex;
    }
    else if (curr_type == LEX_NUM) {
        poliz.push_back(curr_lex);
        poliz.push_back(Lex(LEX_ASSIGN));
        get_lex();
        I3();
    } else
        throw curr_lex;
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
//strings
void Parser::S() {
    if (curr_type == LEX_ID) {
        declare(curr_val, LEX_STRING);
        poliz.push_back(Lex(POLIZ_ADDRESS, curr_val));
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
            poliz.push_back(curr_lex);
            poliz.push_back(Lex(LEX_ASSIGN));
            get_lex();
            S2();
        } else {
            throw curr_lex;
        }
    } else {
        poliz.pop_back();
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
//booleans
void Parser::B() {
    if (curr_type == LEX_ID) {
        declare(curr_val, LEX_BOOL);
        poliz.push_back(Lex(POLIZ_ADDRESS, curr_val));
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
        poliz.pop_back();
        B3();
    }
}
void Parser::B2() {
    if (curr_type == LEX_TRUE || curr_type == LEX_FALSE) {
        if (curr_type == LEX_TRUE) {
            poliz.push_back(Lex(LEX_TRUE, 1));
        } else
            poliz.push_back(Lex(LEX_FALSE, 0));

        poliz.push_back(Lex(LEX_ASSIGN));
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
//commands function
void Parser::C() {
    D();
    while (curr_type == LEX_SEMICOLON) {
        get_lex();
        D();
    }
}
//command function
void Parser::D() {
    int p0, p1, p2, p3;

    if (curr_type == LEX_READ) {
        get_lex();
        if (curr_type == LEX_LPAREN) {
            get_lex();
            if (curr_type == LEX_ID) {
                check_id_in_read();
                poliz.push_back(Lex(POLIZ_ADDRESS, curr_val));
                get_lex();
            }
            else
                throw curr_lex;

            if (curr_type == LEX_RPAREN){
                get_lex();
                poliz.push_back(Lex(LEX_READ));
            } else
                throw curr_lex;
        }
        else
            throw curr_lex;
    }
    else if (curr_type == LEX_IF) {
        get_lex();
        L0();
        eq_bool();
        p2 = (int)poliz.size();
        poliz.push_back(Lex());
        poliz.push_back(Lex(POLIZ_FGO));
        D();
        p3 = (int)poliz.size();

        poliz.push_back(Lex());
        poliz.push_back(Lex(POLIZ_GO));

        poliz[p2] = Lex(POLIZ_LABEL, (int)poliz.size());
        if (curr_type == LEX_ELSE) {
            get_lex();
            D();
            poliz[p3] = Lex(POLIZ_LABEL, (int)poliz.size());
            D();
        }
    }
    else if (curr_type == LEX_WHILE) {
        p0 = (int)poliz.size();
        get_lex();
        L0();
        eq_bool();
        p1 = (int)poliz.size();
        poliz.push_back(Lex());
        poliz.push_back(Lex(POLIZ_FGO));
        D();
        poliz.push_back(Lex(POLIZ_LABEL, p0));
        poliz.push_back(Lex(POLIZ_GO));

        poliz[p1] = Lex(POLIZ_LABEL, (int)poliz.size());
    }
    else if (curr_type == LEX_WRITE) {
        get_lex();
        if (curr_type == LEX_LPAREN) {
            get_lex();
            L0();
            while (curr_type == LEX_COMMA) {
                get_lex();
                L0();
            }
            if (curr_type == LEX_RPAREN) {
                get_lex();
                poliz.push_back(Lex(LEX_WRITE));
            } else
                throw curr_lex;
        }
    }
    else if (curr_type == LEX_ID) {
        check_id();
        poliz.push_back(Lex(POLIZ_ADDRESS, curr_val));
        get_lex();
        if (curr_type == LEX_ASSIGN) {
            get_lex();
            L0();
            eq_type();
            poliz.push_back(Lex(LEX_ASSIGN));
        } else
            throw curr_lex;
    }
    else if (curr_type == LEX_BEGIN) {
        get_lex();
        C();
        if (curr_type == LEX_END) {
            get_lex();
            //D();
        } else
            throw curr_lex;
    }
}
//command logic
void Parser::L0() {
    L1();
    if (curr_type == LEX_ASSIGN) {
        st_lex.push(curr_type);
        get_lex();
        L1();
    }
}
void Parser::L1() {
    L2();
    if (curr_type == LEX_OR) {
        st_lex.push(curr_type);
        get_lex();
        L2();
    }
}
void Parser::L2() {
    L3();
    while (curr_type == LEX_AND) {
        st_lex.push(curr_type);
        get_lex();
        L3();
    }
}
void Parser::L3() {
    L4();
    if (curr_type == LEX_EQ || curr_type == LEX_LSS || curr_type == LEX_GTR ||
        curr_type == LEX_LEQ || curr_type == LEX_GEQ || curr_type == LEX_NEQ) {
        st_lex.push(curr_type);
        get_lex();
        L4();
        check_op();
    }
}
void Parser::L4() {
    T();
    while (curr_type == LEX_PLUS || curr_type == LEX_MINUS) {
        st_lex.push(curr_type);
        get_lex();
        T();
        check_op();
    }
}
void Parser::T() {
    F();
    while (curr_type == LEX_TIMES || curr_type == LEX_SLASH) {
        st_lex.push(curr_type);
        get_lex();
        F();
        check_op();
    }
}
void Parser::F() {
    if (curr_type == LEX_ID) {
        check_id();
        poliz.push_back(Lex(LEX_ID, curr_val));
        get_lex();
    }
    else if (curr_type == LEX_NUM) {
        st_lex.push(LEX_INT);
        poliz.push_back(curr_lex);
        get_lex();
    }
    else if (curr_type == LEX_STRC) {
        st_lex.push(LEX_STRING);
        poliz.push_back(curr_lex);
        get_lex();
    }
    else if (curr_type == LEX_TRUE) {
        st_lex.push(LEX_BOOL);
        poliz.push_back(Lex(LEX_TRUE, 1));
        get_lex();
    }
    else if (curr_type == LEX_FALSE) {
        st_lex.push(LEX_BOOL);
        poliz.push_back(Lex(LEX_FALSE, 0));
        get_lex();
    }
    else if (curr_type == LEX_NOT) {
        get_lex();
        F();
        check_not();
    }
    else if (curr_type == LEX_LPAREN) {
        get_lex();
        L0();
        if (curr_type == LEX_RPAREN)
            get_lex();
        else
            throw curr_lex;
    }
    else if (curr_type == LEX_MINUS) {
        //унарный минус, в поллиз будет закидываться собакой
        //ну работает же, дерьмово, но работает. не трогай бяку
        get_lex();
        if (curr_type == LEX_NUM || (curr_type == LEX_ID &&
        reader.Var_table[curr_lex.show_value()].get_type() == LEX_INT)) {
            st_lex.push(LEX_INT);
            poliz.push_back(curr_lex);
        } else
            throw curr_lex;
        get_lex();
        poliz.push_back(Lex(LEX_UN_MINUS));
    }
    else if (curr_type == LEX_PLUS) {
        get_lex();
        if (curr_type == LEX_NUM || (curr_type == LEX_ID &&
        reader.Var_table[curr_lex.show_value()].get_type() == LEX_INT)) {
            st_lex.push(LEX_INT);
            poliz.push_back(curr_lex);
        } else
            throw curr_lex;
        get_lex();
        poliz.push_back(Lex(LEX_UN_PLUS));

    }
    else
        throw curr_lex;
}

void Parser::check_id () {
    if ( reader.Var_table[curr_val].get_declare() )
        st_lex.push ( reader.Var_table[curr_val].get_type());
    else
        throw "variable is not declared";
}

void Parser::check_op () {
    type_of_lex t1, t2, op;

    t2 = st_lex.top();
    st_lex.pop();

    op = st_lex.top();
    st_lex.pop();

    t1 = st_lex.top();
    st_lex.pop();

    if (op == LEX_PLUS && (t1 == t2)) {
        if (t1 == LEX_INT || t1 == LEX_STRING)
            st_lex.push(t1);
        else
            throw "Unexpected types in operation +";
    } else if (op == LEX_PLUS) {
        throw "Wrong types in operation +";
    }

    if (op == LEX_MINUS || op == LEX_TIMES || op == LEX_SLASH) {
        if (t1 == t2 && t1 == LEX_INT)
            st_lex.push(t1);
        else
            throw "Wrong types in operations -, *, /";
    }

    if (op == LEX_OR || op == LEX_AND) {
        if (t1 == t2 && t1 == LEX_BOOL)
            st_lex.push(t1);
        else
            throw "Wrong types in logic and, or";
    }

    if (op == LEX_EQ || op == LEX_LSS || op == LEX_GTR ||
        op == LEX_LEQ || op == LEX_GEQ || op == LEX_NEQ) {
        if (t1 == t2 && (t1 == LEX_INT || t1 == LEX_STRING || t1 == LEX_BOOL)) {
            st_lex.push(LEX_BOOL);
        } else
            throw "Non-equal types in boolean expression";
     }
     poliz.push_back(Lex(op));
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
    if (!reader.Var_table[curr_val].get_declare())
        throw "not declared";
}

void Parser::declare(int ident, type_of_lex variant) {
    int i;
    for (i = 0; i < st_var.size(); i++) {
        if (st_var[i] == ident)
            break;
    }

    if (i == st_var.size()) {
        st_var.push_back(ident);
        reader.Var_table[ident].put_declare();
    } else
        throw "Second declare of variable";

    switch (variant) {
        case LEX_INT:
            st_int.push_back(ident);
            reader.Var_table[ident].put_type(LEX_INT);
            break;
        case LEX_STRING:
            st_str.push_back(ident);
            reader.Var_table[ident].put_type(LEX_STRING);
            break;
        case LEX_BOOL:
            st_bool.push_back(ident);
            reader.Var_table[ident].put_type(LEX_BOOL);
            break;
        default:
            throw "Unexpected variable type";
    }
}