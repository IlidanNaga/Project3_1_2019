#include "Interpretator.h"

Interpretator::Interpretator(char *file_name) {
    parser.set_file(file_name);
}

int Interpretator::put_TS(const std::string &other) {
    auto iter = TS.begin();
    if ((iter = std::find(TS.begin(), TS.end(), other)) != TS.end())
        return (int)(iter - TS.begin());
    TS.push_back(other);
    return (int)(TS.size() - 1);
}

void Interpretator::launch() {
    parser.analyzis();
    // Here i finally got bored of transmitting the elements
    TS = parser.reader.Str_table;
    TID = parser.reader.Var_table;
    execute(parser.poliz);
}

void Interpretator::print_stack(std::stack<Variable> &st) {
    if (!st.empty()) {
        Variable buf = st.top();
        st.pop();
        if (st.empty()) {
            if (buf.get_type() == LEX_STRING || buf.get_type() == LEX_STRC)
                std::cout << TS[buf.get_value()] << std::endl;
            else
                std::cout << buf.get_value() << std::endl;
        }
        else {
            print_stack(st);
            if (buf.get_type() == LEX_STRING || buf.get_type() == LEX_STRC)
                std::cout << TS[buf.get_value()] << std::endl;
            else
                std::cout << buf.get_value() << std::endl;
        }
    }
}

void Interpretator::execute(std::vector<Lex> &poliz) {
    std::stack<Variable> args;
    Variable a, b;  // reminder:: first operand is ALWAYS b
    int index = 0;
    int size = poliz.size();

    while (index < size) {
        pc_el = poliz[index];
        switch(pc_el.show_type()) {
            case LEX_NUM: case LEX_STRC:
            case LEX_TRUE: case LEX_FALSE:
            case POLIZ_ADDRESS: case POLIZ_LABEL:
                a.put_value(pc_el.show_value());
                a.put_type(pc_el.show_type());

                args.push(a);
                break;

            case LEX_ID:
                if (TID[pc_el.show_value()].get_assign()) {
                    args.push(TID[pc_el.show_value()]);
                    break;
                }
                std::cout << index << "   " << pc_el;
                throw "POLIZ: unknow ID";

            //from now it'll be only operations

            case LEX_ASSIGN:

                a = args.top();
                args.pop();

                b = args.top();
                args.pop();

                if (!args.empty()) // multiple assignment
                    args.push(a);

                TID[b.get_value()].put_value(a.get_value());
                TID[b.get_value()].put_assign();
                break;

            case LEX_UN_MINUS:
                if (args.empty())
                    throw "Error in POLIZ, UN";
                a = args.top();
                args.pop();

                a.put_value(-a.get_value());
                args.push(a);
                break;
            case LEX_UN_PLUS:
                if (args.empty())
                    throw "Error in POLIZ, UN";
                break;

            case LEX_NOT:
                a = args.top();
                args.pop();

                a.put_value(!a.get_value());
                args.push(a);
                break;

            case LEX_AND:
                a = args.top();
                args.pop();

                b = args.top();
                args.pop();

                a.put_value(a.get_value() && b.get_value());
                args.push(a);
                break;
            case LEX_OR:
                a = args.top();
                args.pop();

                b = args.top();
                args.pop();

                a.put_value(a.get_value() || b.get_value());
                args.push(a);
                break;

            case POLIZ_GO:
                a = args.top();
                args.pop();

                index = a.get_value() - 1;
                break;

            case POLIZ_FGO:
                a = args.top();
                args.pop();

                b = args.top();
                args.pop();

                if (!b.get_value())
                    index = a.get_value() - 1;
                break;

            case LEX_WRITE:
                print_stack(args);
                while (!args.empty())
                    args.pop();
                break;

            case LEX_READ:
                int buf;
                a = args.top();
                args.pop();

                if (TID[a.get_value()].get_type() == LEX_INT) {
                    std::cout << "Input int value for variable " << TID[a.get_value()].get_name() << std::endl;
                    std::cin >> buf;
                } else if (TID[a.get_value()].get_type() == LEX_STRING) {
                    std::string s;
                    std::cout << "Input string value for variable " << TID[a.get_value()].get_name() << std::endl;
                    std::getline(std::cin, s);
                    buf = put_TS(s);
                } else {
                    std::string s;
                    std::cout << "Input boolean value (true or false) for variable ";
                    std::cout << TID[a.get_value()].get_name() << std::endl;
                    std::cin >> s;

                    if (s == "true") {
                        buf = 1;
                    } else if (s == "false") {
                        buf = 0;
                    } else
                        throw "POLIZ: Error reading boolean";
                }
                TID[a.get_value()].put_value(buf);
                TID[a.get_value()].put_assign();
                break;

            case LEX_PLUS:

                a = args.top();
                args.pop();

                b = args.top();
                args.pop();

                if (a.get_type() == LEX_STRING || a.get_type() == LEX_STRC)
                    a.put_value(put_TS(TS[b.get_value()] + TS[a.get_value()]));
                else
                    a.put_value(b.get_value() + a.get_value());
                args.push(a);
                break;

            case LEX_MINUS:
            case LEX_TIMES:
            case LEX_SLASH:

                a = args.top();
                args.pop();

                b = args.top();
                args.pop();

                if (pc_el.show_type() == LEX_MINUS)
                    a.put_value(b.get_value() - a.get_value());
                else if (pc_el.show_type() == LEX_TIMES)
                    a.put_value(b.get_value() * a.get_value());
                else {
                    if (a.get_value()) {
                        a.put_value(b.get_value() / a.get_value());
                    } else
                        throw "POLIZ: Division by 0";
                }
                args.push(a);
                break;

            case LEX_EQ:

                a = args.top();
                args.pop();
                b = args.top();
                args.pop();
                if (a.get_type() == LEX_STRING || a.get_type() == LEX_STRC) {
                    a.put_value(TS[b.get_value()] == TS[a.get_value()]);
                    if (a.get_value())
                        a.put_type(LEX_TRUE);
                    else
                        a.put_type(LEX_FALSE);
                }
                else
                    a.put_value(b.get_value() == a.get_value());
                args.push(a);
                break;

            case LEX_LSS:
                a = args.top();
                args.pop();
                b = args.top();
                args.pop();
                if (a.get_type() == LEX_STRING || a.get_type() == LEX_STRC) {
                    a.put_value(TS[b.get_value()] < TS[a.get_value()]);
                    if (a.get_value())
                        a.put_type(LEX_TRUE);
                    else
                        a.put_type(LEX_FALSE);
                }
                else
                    a.put_value(b.get_value() < a.get_value());
                args.push(a);
                break;
            case LEX_GTR:
                a = args.top();
                args.pop();
                b = args.top();
                args.pop();
                if (a.get_type() == LEX_STRING || a.get_type() == LEX_STRC) {
                    a.put_value(TS[b.get_value()] > TS[a.get_value()]);
                    if (a.get_value())
                        a.put_type(LEX_TRUE);
                    else
                        a.put_type(LEX_FALSE);
                }
                else
                    a.put_value(b.get_value() > a.get_value());
                args.push(a);
                break;
            case LEX_LEQ:
                a = args.top();
                args.pop();
                b = args.top();
                args.pop();
                a.put_value(b.get_value() <= a.get_value());
                args.push(a);
                break;
            case LEX_GEQ:
                a = args.top();
                args.pop();
                b = args.top();
                args.pop();
                a.put_value(b.get_value() >= a.get_value());
                args.push(a);
                break;
            case LEX_NEQ:
                a = args.top();
                args.pop();
                b = args.top();
                args.pop();
                if (a.get_type() == LEX_STRING || a.get_type() == LEX_STRC) {
                    a.put_value(TS[b.get_value()] != TS[a.get_value()]);
                    if (a.get_value())
                        a.put_type(LEX_TRUE);
                    else
                        a.put_type(LEX_FALSE);
                }
                else
                    a.put_value(b.get_value() != a.get_value());
                args.push(a);
                break;

            default:

                throw "Unexpected element, POLIZ";
        }
        index ++;
    }
}
