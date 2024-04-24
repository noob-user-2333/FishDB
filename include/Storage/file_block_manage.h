//
// Created by user on 4/22/24.
//

#ifndef STORAGE_FILE_BLOCK_MANAGE_H
#define STORAGE_FILE_BLOCK_MANAGE_H
#include "block_info.h"
#include "file_system.h"
class FileBlockManage {
private:
    std::unique_ptr<FileHandle> handle;
    std::string path;
public:
    explicit FileBlockManage(std::string  path);



};



#endif //STORAGE_FILE_BLOCK_MANAGE_H
