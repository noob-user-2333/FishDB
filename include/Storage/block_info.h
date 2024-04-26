//
// Created by user on 4/20/24.
//

#ifndef STORAGE_BLOCK_INFO_H
#define STORAGE_BLOCK_INFO_H
#include "../../utility.h"


struct DataBaseHeader{

};

struct MainHeader{
    static constexpr int MagicByteLen = 16;
    static constexpr int VersionLen = 16;
    static constexpr char MagicBytes[MagicByteLen] = "DataBase File";
    static constexpr char VersionString[VersionLen] = "v0.0.1";
    char magicNum[MagicByteLen];
    char version[VersionLen];
};



#endif //STORAGE_BLOCK_INFO_H
