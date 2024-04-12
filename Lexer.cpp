//
// Created by user on 23-4-20.
//

#include <iostream>
#include "Lexer.h"

    static const char* TokenTypeName[] = {
            "TOKEN_ZERO",
            "TOKEN_INT",
            "TOKEN_DOUBLE",
            "TOKEN_LB",
            "TOKEN_RB",
            "TOKEN_COMMA",
            "TOKEN_END",
            "TOKEN_DOT",
            "TOKEN_SPACE",
            "TOKEN_MORE",
            "TOKEN_MEQ",
            "TOKEN_LESS",
            "TOKEN_LEQ",
            "TOKEN_EQUAL",
            "TOKEN_PLUS",
            "TOKEN_SUB",
            "TOKEN_STAR",
            "TOKEN_DIV",
            "TOKEN_PERCENT",
            "TOKEN_BITAND",
            "TOKEN_BITOR",
            "TOKEN_AND",
            "TOKEN_OR",
            "TOKEN_XOR",
            "TOKEN_NOTEQUAL",
            "TOKEN_BANG",
            "TOKEN_LSHIFT",
            "TOKEN_RSHIFT",
            "TOKEN_STRING",
            "TOKEN_ID",
            "TOKEN_KW_ASC",
            "TOKEN_KW_BY",
            "TOKEN_KW_CHAR",
            "TOKEN_KW_CREATE",
            "TOKEN_KW_DELETE",
            "TOKEN_KW_DESC",
            "TOKEN_KW_DISTIN",
            "TOKEN_KW_DROP",
            "TOKEN_KW_FLOAT",
            "TOKEN_KW_FROM",
            "TOKEN_KW_GROUP",
            "TOKEN_KW_HAVING",
            "TOKEN_KW_INDEX",
            "TOKEN_KW_INSERT",
            "TOKEN_KW_INT",
            "TOKEN_KW_INTO",
            "TOKEN_KW_JOIN",
            "TOKEN_KW_LONG",
            "TOKEN_KW_ON",
            "TOKEN_KW_ORDER",
            "TOKEN_KW_SELECT",
            "TOKEN_KW_SET",
            "TOKEN_KW_SHORT",
            "TOKEN_KW_TABLE",
            "TOKEN_KW_UPDATE",
            "TOKEN_KW_VALUES",
            "TOKEN_KW_VCHAR",
            "TOKEN_KW_WHERE"};

    int Lexer::TokenAnalysis(const char *pTokenStart, int *pType, int *pLen) {
        int type = (int) typeMap[pTokenStart[0]];
        switch (type) {
            case TOKEN_ZERO:
            case TOKEN_LB:
            case TOKEN_RB:
            case TOKEN_COMMA:
            case TOKEN_END:
            case TOKEN_PLUS:
            case TOKEN_SUB:
            case TOKEN_STAR:
            case TOKEN_DIV:
            case TOKEN_PERCENT:
            case TOKEN_XOR:
            case TOKEN_DOT:
                *pType = type;
                *pLen = 1;
                return 0;
            case TOKEN_MORE: {
                if (pTokenStart[1] == '=') {
                    *pType = TOKEN_MEQ;
                    *pLen = 2;
                } else if (pTokenStart[1] == '>') {
                    *pType = TOKEN_RSHIFT;
                    *pLen = 2;
                } else {
                    *pType = type;
                    *pLen = 1;
                }
                return 0;
            }
            case TOKEN_LESS: {
                if (pTokenStart[1] == '=') {
                    *pType = TOKEN_LEQ;
                    *pLen = 2;

                } else if (pTokenStart[1] == '<') {
                    *pType = TOKEN_LSHIFT;
                    *pLen = 2;
                } else {
                    *pType = type;
                    *pLen = 1;
                }
                return 0;
            }
            case TOKEN_BANG: {
                if (pTokenStart[1] == '=') {
                    *pType = TOKEN_NOTEQUAL;
                    *pLen = 2;
                } else {
                    *pType = type;
                    *pLen = 1;
                }
                return 0;
            }
            case TOKEN_EQUAL: {
                if (pTokenStart[1] == '=')
                    *pLen = 2;
                else
                    *pLen = 1;
                *pType = TOKEN_EQUAL;
                return 0;
            }
            case TOKEN_BITAND: {
                if (pTokenStart[1] == '&') {
                    *pType = TOKEN_AND;
                    *pLen = 2;
                } else {
                    *pType = type;
                    *pLen = 1;
                }
                return 0;
            }
            case TOKEN_BITOR: {
                if (pTokenStart[1] == '|') {
                    *pType = TOKEN_OR;
                    *pLen = 2;
                } else {
                    *pType = type;
                    *pLen = 1;
                }
                return 0;
            }
            case TOKEN_INT: {
                //区分16进制和非16的进制
                if (pTokenStart[0] == '0' && pTokenStart[1] == 'x') {
                    int len = 2;
                    if (NumIdentify[pTokenStart[2]] == 0)
                        return -1;
                    while (NumIdentify[pTokenStart[len]])
                        len++;
                    *pType = TOKEN_INT;
                    *pLen = len;
                    return 0;
                }
                int len = 0;
                *pType = TOKEN_INT;
                while (NumIdentify[pTokenStart[len]] & 1)
                    len++;
                if (pTokenStart[len] == '.') {
                    *pType = TOKEN_DOUBLE;
                    len++;
                    if ((NumIdentify[pTokenStart[len]] & 1) == 0)
                        return -1;
                    while (NumIdentify[pTokenStart[len]] & 1)
                        len++;
                }
                *pLen = len;
                return 0;
            }
            case TOKEN_ID: {
                int len = 0;
                while (IDIdentify[pTokenStart[len]])
                    len++;
                *pLen = len;
                //除去可能为id外还可能是关键字
                *pType = TOKEN_ID + 1 + KeywordSearch(pTokenStart, len);
                return 0;
            }
            case TOKEN_STRING: {
                *pType = TOKEN_STRING;
                int len = 1;
                while (pTokenStart[len]) {
                    if (pTokenStart[len] == '\'') {
                        len++;
                        if (pTokenStart[len] != '\'') {
                            *pLen = len;
                            return 0;
                        }
                    }
                    len++;
                }
                return -1;
            }
            case TOKEN_SPACE: {
                int len = 0;
                while (typeMap[pTokenStart[len]] == TOKEN_SPACE)
                    len++;
                *pType = TOKEN_SPACE;
                *pLen = len;
                return 0;
            }
            default:
                return -1;
        }

    }

    int Lexer::KeywordSearch(const char *pStart, int len) {
        int start = keywordHash[*pStart];
        //确定是否存在相应首字母的关键字
        if (start >= 0) {
            //确定pos不会越界
            while (start < 28) {
                auto keyword = keywords[start];
                //如果首字母不同则说明不存在相应关键字
                if (keyword[0] == *pStart) {
                    //长度相等才可能一致
                    if (keywordsLen[start] == len) {
                        int i;
                        for (i = 0; i < len; i++) {
                            if (keyword[i] != pStart[i])
                                break;
                        }
                        if (i == len)
                            return start;
                    }
                    start++;
                    continue;
                }
                return -1;
            }
        }
        return -1;
    }

    int Lexer::GetToken(const char *pString, int *pOffset, int *pType, int *pLen) {
        assert(pString && pOffset && pType && pLen);
        auto pStart = pString + *pOffset;
        auto res = TokenAnalysis(pStart, pType, pLen);
        *pOffset += *pLen;
        return res;
    }

    int Lexer::LexerAnalysis(std::list<Lexer::Token> &tokenList, const char *sqlString) {
        assert( sqlString );
        tokenList.clear();
        auto count = 0;
        auto offset = 0;
        auto type = 0;
        auto len = 0;
        auto res = 0;
        auto originOffset = offset;
        res = GetToken(sqlString, &offset, &type, &len);
        while (res == ErrorCode::Success && type != TOKEN_ZERO) {
            if (type != TOKEN_SPACE) {
                if (type != TOKEN_ID)
                    tokenList.emplace_back(type);
                else
                    tokenList.emplace_back(type, sqlString,originOffset, len);
                count++;
            }
            originOffset = offset;
            res = GetToken(sqlString, &offset, &type, &len);
        }
        return ErrorCode::Success;
    }

    void Lexer::LexerPrint(std::list<Lexer::Token> &tokenList) {
        int i = 0;
        for (const auto &token: tokenList) {
            auto type = token.type;
            if(type == TOKEN_ID)
                printf("token(%d) type is %s,content is %s\n", i,TokenTypeName[type],token.pStr->c_str());
            else
                printf("token(%d) type is %s\n", i,TokenTypeName[type]);
            i++;
        }
    }


