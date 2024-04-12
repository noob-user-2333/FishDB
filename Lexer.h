//
// Created by user on 23-4-20.
//

#ifndef DATAOPERATE_LEXER_H
#define DATAOPERATE_LEXER_H

#include "utility.h"



    class Lexer {
    private:
        constexpr const static char typeMap[128] = {0, -1, -1, -1, -1, -1, -1, -1, -1, 8, 8, -1, -1, 8, -1, -1,
                                                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                    8, 25, -1, -1, -1, 18, 19, 28, 3, 4, 16, 14, 5, 15, 7, 17,
                                                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 6, 11, 13, 9, -1,
                                                    -1, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
                                                    29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, -1, -1, -1, 23, 29,
                                                    -1, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
                                                    29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, -1, 20, -1, -1, -1,
        };
        constexpr const static char NumIdentify[128] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0,
                                                        0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                        0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        };

        constexpr const static char IDIdentify[128] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
                                                       0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                                       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
                                                       0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                                       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        };
        constexpr static const char *keywords[28] = {"asc", "by", "char", "create", "delete",
                                                     "desc", "distinct", "drop", "float", "from",
                                                     "group", "having", "index", "insert", "int",
                                                     "into", "join", "long", "on", "order",
                                                     "select", "set", "short", "table", "update",
                                                     "values", "vchar", "where"};
        static constexpr char  keywordsLen[28] = { 3, 2, 4, 6, 6, 4, 8, 4,
                                                   5, 4, 5, 6, 5, 6, 3, 4,
                                                   4, 4, 2, 5, 6, 3, 5, 5,
                                                   6, 6, 5, 5};
        constexpr static const char keywordHash[128] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                                        -1, 0, 1, 2, 4, -1, 8, 10, 11, 12, 16, -1, 17, -1, -1, 18,
                                                        -1, -1, -1, 20, 23, 24, 25, 27, -1, -1, -1, -1, -1, -1, -1,
                                                        -1};

        static int TokenAnalysis(const char *pTokenStart, int *pType, int *pLen);

        static int KeywordSearch(const char *pStart, int len);

        static int GetToken(const char *pString, int *pOffset, int *pType, int *pLen);

    public:

        static constexpr int TOKEN_ZERO = 0;
        static constexpr int TOKEN_INT = 1;
        static constexpr int TOKEN_DOUBLE = 2;
        static constexpr int TOKEN_LB = 3;
        static constexpr int TOKEN_RB = 4;
        static constexpr int TOKEN_COMMA = 5;
        static constexpr int TOKEN_END = 6;
        static constexpr int TOKEN_DOT = 7;
        static constexpr int TOKEN_SPACE = 8;
        static constexpr int TOKEN_MORE = 9;
        static constexpr int TOKEN_MEQ = 10;
        static constexpr int TOKEN_LESS = 11;
        static constexpr int TOKEN_LEQ = 12;
        static constexpr int TOKEN_EQUAL = 13;
        static constexpr int TOKEN_PLUS = 14;
        static constexpr int TOKEN_SUB = 15;
        static constexpr int TOKEN_STAR = 16;
        static constexpr int TOKEN_DIV = 17;
        static constexpr int TOKEN_PERCENT = 18;
        static constexpr int TOKEN_BITAND = 19;
        static constexpr int TOKEN_BITOR = 20;
        static constexpr int TOKEN_AND = 21;
        static constexpr int TOKEN_OR = 22;
        static constexpr int TOKEN_XOR = 23;
        static constexpr int TOKEN_NOTEQUAL = 24;
        static constexpr int TOKEN_BANG = 25;
        static constexpr int TOKEN_LSHIFT = 26;
        static constexpr int TOKEN_RSHIFT = 27;
        static constexpr int TOKEN_STRING = 28;
        static constexpr int TOKEN_ID = 29;
        static constexpr int TOKEN_KW_ASC = (TOKEN_ID + 1);
        static constexpr int TOKEN_KW_BY = (TOKEN_ID + 2);
        static constexpr int TOKEN_KW_CHAR = (TOKEN_ID + 3);
        static constexpr int TOKEN_KW_CREATE = (TOKEN_ID + 4);
        static constexpr int TOKEN_KW_DELETE = (TOKEN_ID + 5);
        static constexpr int TOKEN_KW_DESC = (TOKEN_ID + 6);
        static constexpr int TOKEN_KW_DISTINCT = (TOKEN_ID + 7);
        static constexpr int TOKEN_KW_DROP = (TOKEN_ID + 8);
        static constexpr int TOKEN_KW_FLOAT = (TOKEN_ID + 9);
        static constexpr int TOKEN_KW_FROM = (TOKEN_ID + 10);
        static constexpr int TOKEN_KW_GROUP = (TOKEN_ID + 11);
        static constexpr int TOKEN_KW_HAVING = (TOKEN_ID + 12);
        static constexpr int TOKEN_KW_INDEX = (TOKEN_ID + 13);
        static constexpr int TOKEN_KW_INSERT = (TOKEN_ID + 14);
        static constexpr int TOKEN_KW_INT = (TOKEN_ID + 15);
        static constexpr int TOKEN_KW_INTO = (TOKEN_ID + 16);
        static constexpr int TOKEN_KW_JOIN = (TOKEN_ID + 17);
        static constexpr int TOKEN_KW_LONG = (TOKEN_ID + 18);
        static constexpr int TOKEN_KW_ON = (TOKEN_ID + 19);
        static constexpr int TOKEN_KW_ORDER = (TOKEN_ID + 20);
        static constexpr int TOKEN_KW_SELECT = (TOKEN_ID + 21);
        static constexpr int TOKEN_KW_SET = (TOKEN_ID + 22);
        static constexpr int TOKEN_KW_SHORT = (TOKEN_ID + 23);
        static constexpr int TOKEN_KW_TABLE = (TOKEN_ID + 24);
        static constexpr int TOKEN_KW_UPDATE = (TOKEN_ID + 25);
        static constexpr int TOKEN_KW_VALUES = (TOKEN_ID + 26);
        static constexpr int TOKEN_KW_VCHAR = (TOKEN_ID + 27);
        static constexpr int TOKEN_KW_WHERE = (TOKEN_ID + 28);

        struct Token {
            int type;
            std::string *pStr;
            Token *pLChild;
            Token *pRChild;
            explicit Token(int type) : type(type),pStr(nullptr),pLChild(nullptr), pRChild(nullptr){
                assert(type != TOKEN_ID);
            }
            Token(int type,const char *pString,int offset,int len) : type(type),pStr(nullptr),pLChild(nullptr),pRChild(nullptr){
                assert(type == TOKEN_ID && pString);
                pStr = new std::string(pString + offset,len);
            }
            ~Token(){delete pStr;}
        };


        Lexer() = delete;

        static int LexerAnalysis(std::list<Token> & tokenList, const char *sqlString);

        static void LexerPrint(std::list<Token>& tokenList);

    };
    typedef std::list<Lexer::Token> TokenList;

#endif //DATAOPERATE_LEXER_H
