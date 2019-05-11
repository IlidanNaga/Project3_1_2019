#include "Lex.h"



type_of_lex Lex::show_type() {
    return Lex_type;
}

int Lex::show_value() {
    return value;
}

std::ostream& operator<<(std::ostream &out, Lex l) {
    switch(l.Lex_type) {
        case 0:
            out << "(LEX_NULL, " << l.value << ");";
            break;
        case 1:
            out << "(LEX_AND, " << l.value << ");";
            break;
        case 2:
            out << "(LEX_BEGIN, " << l.value << ");";
            break;
        case 3:
            out << "(LEX_BOOL, " << l.value << ");";
            break;
        case 4:
            out << "(LEX_DO, " << l.value << ");";
            break;
        case 5:
            out << "(LEX_ELSE, " << l.value << ");";
            break;
        case 6:
            out << "(LEX_END, " << l.value << ");";
            break;
        case 7:
            out << "(LEX_IF, " << l.value << ");";
            break;
        case 8:
            out << "(LEX_FALSE, " << l.value << ");";
            break;
        case 9:
            out << "(LEX_INT, " << l.value << ");";
            break;
        case 10:
            out << "(LEX_STRING, " << l.value << ");";
            break;
        case 11:
            out << "(LEX_NOT, " << l.value << ");";
            break;
        case 12:
            out << "(LEX_OR, " << l.value << ");";
            break;
        case 13:
            out << "(LEX_PROGRAM, " << l.value << ");";
            break;
        case 14:
            out << "(LEX_READ, " << l.value << ");";
            break;
        case 15:
            out << "(LEX_TRUE, " << l.value << ");";
            break;
        case 16:
            out << "(LEX_WHILE, " << l.value << ");";
            break;
        case 17:
            out << "(LEX_WRITE, " << l.value << ");";
            break;
        case 18:
            out << "(LEX_FIN, " << l.value << ");";
            break;
        case 19:
            out << "(LEX_SEMICOLON, " << l.value << ");";
            break;
        case 20:
            out << "(LEX_COMMA, " << l.value << ");";
            break;
        case 21:
            out << "(LEX_COLON, " << l.value << ");";
            break;
        case 22:
            out << "(LEX_ASSIGN, " << l.value << ");";
            break;
        case 23:
            out << "(LEX_LPAREN, " << l.value << ");";
            break;
        case 24:
            out << "(LEX_RPAREN, " << l.value << ");";
            break;
        case 25:
            out << "(LEX_EQ, " << l.value << ");";
            break;
        case 26:
            out << "(LEX_LSS, " << l.value << ");";
            break;
        case 27:
            out << "(LEX_GTR, " << l.value << ");";
            break;
        case 28:
            out << "(LEX_PLUS, " << l.value << ");";
            break;
        case 29:
            out << "(LEX_MINUS, " << l.value << ");";
            break;
        case 30:
            out << "(LEX_TIMES, " << l.value << ");";
            break;
        case 31:
            out << "(LEX_SLASH, " << l.value << ");";
            break;
        case 32:
            out << "(LEX_LEQ, " << l.value << ");";
            break;
        case 33:
            out << "(LEX_NEQ, " << l.value << ");";
            break;
        case 34:
            out << "(LEX_GEQ, " << l.value << ");";
            break;
        case 35:
            out << "(LEX_NUM, " << l.value << ");";
            break;
        case 36:
            out << "(LEX_STRC, " << l.value << ");";
            break;
        case 37:
            out << "(LEX_ID, " << l.value << ");";
            break;
        case 38:
            out << "(POLIZ_LABEL, " << l.value << ");";
            break;
        case 39:
            out << "(POLIZ_ADDRESS, " << l.value << ");";
            break;
        case 40:
            out << "(POLIZ_GO, " << l.value << ");";
            break;
        case 41:
            out << "(POLIZ_FGO, " << l.value << ");";
            break;
        default:
            throw "unexpected lexeme";
    }
    return out;
}
