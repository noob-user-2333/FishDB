//
// Created by user on 4/23/24.
//

#include "../../include/Storage/file_block_manage.h"

#include <utility>

FileBlockManage::FileBlockManage(std::string  path):path(std::move(path)),handle(nullptr) {
}
