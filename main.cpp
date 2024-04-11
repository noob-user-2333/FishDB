#include "Lexer.h"
using namespace fishDB;
char sql[] = "select * from test where id >= 1200;";


int main() {
    TokenList list;
    Lexer::LexerAnalysis(list,sql);
    Lexer::LexerPrint(list);
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
