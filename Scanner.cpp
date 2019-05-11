#include "Scanner.h"


const char *Scanner::TW[] =
        {
                "", "and", "{", "boolean", "do", "else", "}", "if", "false", "int", "string",
                "not", "or", "program", "read", "true", "while", "write", NULL
        };

const char *Scanner::TD[] =
        {
                "", ";", ",", ":", "=", "(", ")", "==", "<",
                ">", "+", "-", "*", "/", "<=", "!=", ">=", NULL
        };

int Scanner::put_var(const std::string &other) {
    int i;
    for (i = 0; i < Var_table.size(); i++) {
        if (Var_table[i].get_name() == other)
            break;
    }
    if (i < Var_table.size())
        return i;
    Var_table.push_back(Variable(other));
    return (int)(Var_table.size() - 1);
}

int Scanner::put_str(const std::string &other) {
    auto iter = Str_table.begin();
    if ((iter = std::find(Str_table.begin(), Str_table.end(), other)) != Str_table.end())
        return (int)(iter - Str_table.begin());
    Str_table.push_back(other);
    return (int)(Str_table.size() - 1);
}

Scanner::Scanner(char * file_name) {
    if ((fin = fopen(file_name, "r")) == NULL)
        throw "Cannot open a file";
}

void Scanner::set_file(char * file_name) {
    fin = fopen(file_name,"r");
}

void Scanner::get_char() {
    buff = fgetc(fin);
}

void Scanner::unget_char(char c) {
    ungetc(c, fin);
}

int Scanner::look(const std::string &buf, const char **list) {
    int i = 0;
    while (list[i]) {
        if (buf == list[i])
            return i;
        i++;
    }
    return 0;
}

Lex Scanner::get_lex() {
    std::string str_buf;
    int int_buf;
    char a = '0';
    int shift;

    state Curr_state = Start;

    do {
        get_char();
        switch (Curr_state) {
            case Start:

                if (a != '/' && (buff == ' ' || buff == '\n' || buff == '\r' || buff == '\t'));
                else if (a != '/' && isalpha(buff)) {
                    str_buf.push_back(buff);
                    Curr_state = Var;
                }
                else if (a != '/' && isdigit(buff)) {
                    int_buf = buff - '0';
                    Curr_state = Numb;
                }
                else if (a != '/' && buff == '"') {
                    Curr_state = Str;
                }
                else if (a != '/' && buff == '/') {
                    a = '/';
                }
                else if (a == '/' && buff == '*') {
                    a = '0';
                    Curr_state = Comment;
                }
                else if (a != '/' && (buff == '=' || buff == '<' || buff == '>')) {
                    str_buf.push_back(buff);
                    Curr_state = Logic;
                }
                else if (a != '/' && buff == EOF) {
                    return Lex(LEX_FIN);
                }
                else if (a != '/' && buff == '!') {
                    str_buf.push_back(buff);
                    Curr_state = Corner_state;
                }
                else {
                    if (a == '/') {
                        unget_char(buff);
                        buff = a;
                        a = '0';
                    }
                    str_buf.push_back(buff);
                    if ((shift = look(str_buf, TD))) {
                        return Lex((type_of_lex)(shift+(int)LEX_FIN), shift);
                    }
                    else if (str_buf == "{"){
                        return Lex(LEX_BEGIN, 2);
                    }
                    else if (str_buf == "}") {
                        return Lex(LEX_END, 6);
                    }
                    else
                        throw buff;
                }
                break;
            case Var:
                if (isalpha(buff) || isdigit(buff))
                    str_buf.push_back(buff);
                else {
                    unget_char(buff);
                    if ((shift = look(str_buf, TW)))
                        return Lex((type_of_lex)shift, shift);
                    else {
                        shift = put_var(str_buf);
                        return Lex(LEX_ID, shift);
                    }
                }
                break;

            case Str:
                if (buff == EOF)
                    throw buff;
                else if (buff != '"')
                    str_buf.push_back(buff);
                else {
                    shift = put_str(str_buf);
                    return Lex(LEX_STRC, shift);
                }
                break;

            case Numb:

                if (isdigit(buff)) {
                    int_buf = int_buf * 10 + (buff - '0');
                }
                else {
                    unget_char(buff);
                    return Lex(LEX_NUM, int_buf);
                }

                break;

            case Comment:

                if (buff == '*')
                    a = '*';
                else if (a == '*' && buff == '/') {
                    a = '0';
                    Curr_state = Start;
                }
                else if (buff == EOF)
                    throw buff;

                break;

            case Logic:

                if (buff == '=') {
                    str_buf.push_back(buff);
                    shift = look(str_buf, TD);
                    return Lex((type_of_lex)(shift + (int)LEX_FIN), shift);
                }
                else {
                    unget_char(buff);
                    shift = look(str_buf, TD);
                    return Lex((type_of_lex)(shift + (int)LEX_FIN), shift);
                }

                break;

            case Corner_state:
                if (buff == '=') {
                    str_buf.push_back(buff);
                    shift = look(str_buf, TD);
                    return Lex(LEX_NEQ, shift);
                }
                throw '!';
                break;

            default:
                throw int_buf;
                break;
        }
    } while (true);
}

void Scanner::build_table() {
    Lex curr;
    do {
        curr = get_lex();
        Lex_table.push_back(curr);
        std::cout << curr;
    } while (curr.show_type() != LEX_FIN);
}