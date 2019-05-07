#include "Lex.h"



Lex::Lex() {
    Lex_type = Lex_Null;
}

Lex::Lex(class Lex &other) {
    Lex_type = other.Lex_type;
}

type_of_lex Lex::show_type() {
    return Lex_type;
}


/*
 * Lexeme
 * Identifier
 * Scanner
 * Parser
 */