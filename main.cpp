#include "Lexer.h"
char sql[] = "select * from test where id >= 1200 && score * (id + value) >= 0x15000;";


int main() {
    TokenList list;
    Lexer::LexerAnalysis(list,sql);
    Lexer::LexerPrint(list);

    return 0;
}
