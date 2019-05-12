#include "Interpretator.h"

Interpretator::Interpretator(char *file_name) {
    parser.set_file(file_name);
}

void Interpretator::launch() {
    parser.analyzis();
    execute(parser.poliz);
}

void Interpretator::execute(std::vector<Lex> & poliz ) {
    std::stack < int > args;
    int i, j, index = 0, size = poliz.size();
    while ( index < size ) {
        pc_el = poliz [ index ];

        switch ( pc_el.show_type () ) {

            case LEX_TRUE: case LEX_FALSE: case LEX_NUM: case POLIZ_ADDRESS: case POLIZ_LABEL:
                args.push ( pc_el.show_value () );
                break;

            case LEX_ID:
                i = pc_el.show_value ();
                if ( parser.reader.Var_table[i].get_assign () ) {
                    args.push ( parser.reader.Var_table[i].get_value());
                    break;
                }
                else
                    throw "POLIZ: indefinite identifier";

            case LEX_NOT:
                i = args.top();
                args.pop();
                args.push( !i );
                break;

            case LEX_OR:
                i = args.top();
                args.pop();
                j = args.top();
                args.pop();
                args.push ( j || i );
                break;

            case LEX_AND:
                i = args.top();
                args.pop();
                j = args.top();
                args.pop();
                args.push ( j && i );
                break;

            case POLIZ_GO:
                i = args.top();
                args.pop();
                index = i - 1;
                break;

            case POLIZ_FGO:
                i = args.top();
                args.pop();
                j = args.top();
                args.pop();
                if ( !j ) index = i-1;
                break;

            case LEX_WRITE:
                j = args.top();
                args.pop();
                std::cout << j << std::endl;
                break;

            case LEX_READ:
                int k;
                i = args.top ();
                args.pop();
                if ( parser.reader.Var_table[i].get_type () == LEX_INT ) {
                    std::cout << "Input int value for" << parser.reader.Var_table[i].get_name () << std::endl;
                    std::cin >> k;
                }
                else {
                    std::string j;
                    while (1){
                        std::cout << "Input boolean value (true or false) for" << parser.reader.Var_table[i].get_name() << std::endl;
                        std::cin >> j;
                        if (j != "true" && j != "false"){
                            std::cout << "Error in input:true/false" << std::endl;
                            continue;
                        }
                        k = (j == "true")? 1 : 0 ;
                        break;
                    }
                }
                parser.reader.Var_table[i].put_value (k);
                parser.reader.Var_table[i].put_assign ();
                break;

            case LEX_PLUS:
                i = args.top();
                args.pop();
                j = args.top();
                args.pop();
                args.push ( i + j );
                break;

            case LEX_TIMES:
                i = args.top();
                args.pop();
                j = args.top();
                args.pop();
                args.push ( i * j );
                break;

            case LEX_MINUS:
                i = args.top();
                args.pop();
                j = args.top();
                args.pop();
                args.push ( j - i );
                break;

            case LEX_SLASH:
                i = args.top();
                args.pop();
                j = args.top();
                args.pop();
                if (!i) {
                    args.push(j / i);
                    break;
                }
                else
                    throw "POLIZ:divide by zero";

            case LEX_EQ:
                i = args.top();
                args.pop();
                j = args.top();
                args.pop();
                args.push ( i == j);
                break;

            case LEX_LSS:
                i = args.top();
                args.pop();
                j = args.top();
                args.pop();
                args.push ( j < i);
                break;

            case LEX_GTR:
                i = args.top();
                args.pop();
                j = args.top();
                args.pop();
                args.push ( j > i );
                break;

            case LEX_LEQ:
                i = args.top();
                args.pop();
                j = args.top();
                args.pop();
                args.push ( j <= i );
                break;

            case LEX_GEQ:
                i = args.top();
                args.pop();
                j = args.top();
                args.pop();
                args.push ( j >= i );
                break;

            case LEX_NEQ:
                i = args.top();
                args.pop();
                j = args.top();
                args.pop();
                args.push ( j != i );
                break;

            case LEX_ASSIGN:
                i = args.top();
                args.pop();
                j = args.top();
                args.pop();
                parser.reader.Var_table[j].put_value(i);
                parser.reader.Var_table[j].put_assign();
                break;

            default:
                throw "POLIZ: unexpected elem";
        }//end of switch
        ++index;
    };//end of while
    std::cout << "Finish of executing!!!" << std::endl;
}