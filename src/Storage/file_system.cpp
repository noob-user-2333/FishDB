//
// Created by user on 4/23/24.
//

#include "../../include/Storage/file_system.h"
#include <unistd.h>



void FileSystem::SetWorkingDirectory(const std::string &path) {
    auto res = chdir(path.c_str());
    if(res) {
        char info[128];
        sprintf(info,"can not set working directory to %s",path.c_str());
        throw std::runtime_error(info);
    }
}

std::string FileSystem::GetWorkingDirectory() {
    return get_current_dir_name();
}

std::string FileSystem::GetHomeDirectory() {
    return GetEnvVariable("HOME");
}

bool FileSystem::IsPathAbsolute(const std::string &path) {
    return path[0] == '/';
}

std::string FileSystem::JoinPath(const std::string &a, const std::string &b) {
    return a.empty() ? b : a + "/" + b;
}

std::string FileSystem::GetEnvVariable(const std::string &name) {
    return getenv(name.c_str());
}

std::string FileSystem::ExtractName(const std::string &path) {
    auto pos = path.find_last_of('/');
    return {path,pos + 1};
}




std::unique_ptr<FileHandle> FileSystem::OpenFile(const std::string &path, int64_t flags) {
    throw std::logic_error("the api is not implemented");
}

void FileSystem::Read(FileHandle &handle, void *buffer, int64_t bytes, off_t location) {
    throw std::logic_error("the api is not implemented");
}

void FileSystem::Write(FileHandle &handle, void *buffer, int64_t bytes, off_t location) {
throw std::logic_error("the api is not implemented");
}

int64_t FileSystem::Read(FileHandle &handle, void *buffer, int64_t bytes) {
   throw std::logic_error("the api is not implemented");
}

int64_t FileSystem::Write(FileHandle &handle, void *buffer, int64_t bytes) {
    throw std::logic_error("the api is not implemented");
}

int64_t FileSystem::GetFileSize(FileHandle &handle) {
    throw std::logic_error("the api is not implemented");
}

time_t FileSystem::GetLastModifiedTime(FileHandle &handle) {
    throw std::logic_error("the api is not implemented");
}

void FileSystem::Truncate(FileHandle &handle, int64_t new_size) {
    throw std::logic_error("the api is not implemented");
}

bool FileSystem::DirectoryExists(const std::string &directory) {
    throw std::logic_error("the api is not implemented");
}

void FileSystem::CreateDirectory(const std::string &directory) {
    throw std::logic_error("the api is not implemented");
}

bool FileSystem::FileExists(const std::string &filename) {
    throw std::logic_error("the api is not implemented");
}

void FileSystem::RemoveFile(const std::string &filename) {
    throw std::logic_error("the api is not implemented");
}

void FileSystem::FileSync(FileHandle &handle) {
    throw std::logic_error("the api is not implemented");
}

void FileSystem::Seek(FileHandle &handle, off_t location) {
    throw std::logic_error("the api is not implemented");
}

off_t FileSystem::GetSeek(FileHandle &handle) {
    throw std::logic_error("the api is not implemented");
}

void FileSystem::Reset(FileHandle &handle) {
    throw std::logic_error("the api is not implemented");
}


void FileHandle::Close() const {
    close(fd);
}

int64_t FileHandle::Read(void *buffer, int64_t bytes) {
    return file_system.Read(*this,buffer, bytes);
}

int64_t FileHandle::Write(void *buffer, int64_t bytes) {
    return file_system.Write(*this,buffer,bytes);
}

void FileHandle::Read(void *buffer, int64_t bytes, off_t location) {
    file_system.Read(*this,buffer,bytes,location);
}

void FileHandle::Write(void *buffer, int64_t bytes, off_t location) {
file_system.Write(*this,buffer,bytes,location);
}

void FileHandle::Seek(off_t location) {
    file_system.Seek(*this,location);
}

void FileHandle::Reset() {
file_system.Reset(*this);
}

off_t FileHandle::GetSeek() {
    return file_system.GetSeek(*this);
}

void FileHandle::Sync() {
    file_system.FileSync(*this);
}

void FileHandle::Truncate(int64_t new_size) {
    file_system.Truncate(*this,new_size);
}

size_t FileHandle::GetFileSize() {
    return file_system.GetFileSize(*this);
}
