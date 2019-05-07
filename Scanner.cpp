#include "Scanner.h"



Scanner::Scanner(char *file_name) {
    fin = fopen(file_name, "r");
}

void Scanner::get_char() {
    buff = getc(fin);
}

void Scanner::unget_char(char c) {
    ungetc(c, fin);
}

Lex Scanner::get_lex() {

}
