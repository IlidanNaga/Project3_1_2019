#include "Interpretator.h"


int main() {

    try {
        Interpretator Initialisation((char*)"test.txt");
        Initialisation.launch();
    }
    catch (char c) {
        std::cout << "Unexpected symbol: " << c << std::endl;
        return 1;
    }
    catch (Lex l) {
        std::cout << "Unexpected lexeme: " << l << std::endl;
        return 1;
    }
    catch (const char * s) {
        std::cout << s << std::endl;
        return 1;
    }
    catch(...) {
        std::cout << "Something strange happened" << std::endl;
        return 1;
    }

    return 0;
}