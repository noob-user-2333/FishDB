//
// Created by user on 4/23/24.
//

#include "../../include/Storage/unix_file_system.h"
#include <fcntl.h>
#include <sys/stat.h>
FileSystem &FileSystem::Get() {
    static UnixFileSystem local;
    return local;
}
std::unique_ptr<FileHandle> UnixFileSystem::OpenFile(const std::string &path,int64_t flags) {
    int oflag = 0;
    if(flags & FileOpenFlags::FILE_FLAGS_READ)
        oflag = O_RDONLY;
    if(flags & FileOpenFlags::FILE_FLAGS_WRITE)
        oflag = O_WRONLY;
    if(flags & FileOpenFlags::FILE_FLAGS_READ_AND_WRITE)
        oflag = O_RDWR;
    if(flags & FileOpenFlags::FILE_FLAGS_CREATE)
        oflag |= O_CREAT;
    if(flags & FileOpenFlags::FILE_FLAGS_CREATE_NEW)
        oflag |= O_CREAT | O_TRUNC;
    if(flags & FileOpenFlags::FILE_FLAGS_APPEND)
        oflag |= O_APPEND;
    if(oflag & FileOpenFlags::FILE_FLAGS_DIRECT_IO)
        oflag |= O_DIRECT;
    int fd = open(path.c_str(), oflag,0666);
    if (fd == -1) {
        char info[1024];
        sprintf(info, "open file %s failed", path.c_str());
        throw std::runtime_error(info);
    }

    auto p = std::make_unique<FileHandle>(*this,path,fd);
    return std::move(p);
}
int64_t UnixFileSystem::Read(FileHandle &handle, void *buffer, int64_t bytes) {
    return read(handle.fd,buffer,bytes);
}

void UnixFileSystem::Seek(FileHandle &handle, off_t location) {
    lseek(handle.fd,location,SEEK_SET);
}

int64_t UnixFileSystem::Write(FileHandle &handle, void *buffer, int64_t bytes) {
    return write(handle.fd,buffer,bytes);
}

void UnixFileSystem::Read(FileHandle &handle, void *buffer, int64_t bytes, off_t location) {
    Seek(handle,location);
    auto res = Read(handle,buffer,bytes);
    if(res != bytes) {
        char info[128];
        sprintf(info,"can not read all bytes from file: wanted=%ld, get=%ld", res, location);
        throw std::runtime_error(info);
    }
}

void UnixFileSystem::Write(FileHandle &handle, void *buffer, int64_t bytes, off_t location) {
    Seek(handle,location);
    auto res = Write(handle,buffer,bytes);
    if(res != bytes) {
        char info[128];
        sprintf(info,"can not write all bytes to file: wanted=%ld, write=%ld", res, location);
        throw std::runtime_error(info);
    }
}

off_t UnixFileSystem::GetSeek(FileHandle &handle) {
    return lseek(handle.fd, 0, SEEK_CUR);
}

void UnixFileSystem::Reset(FileHandle &handle) {
    Seek(handle,0);
}

int64_t UnixFileSystem::GetFileSize(FileHandle &handle) {
    struct stat buf{};
    auto res = fstat(handle.fd,&buf);
    if(res)
        return res;
    return buf.st_size;
}

time_t UnixFileSystem::GetLastModifiedTime(FileHandle &handle) {
    struct stat buf{};
    auto res = fstat(handle.fd,&buf);
    if(res)
        return res;
    auto time = buf.st_mtim;
    return  time.tv_sec;
}


void UnixFileSystem::Truncate(FileHandle &handle, int64_t new_size) {
    auto res = ftruncate(handle.fd,new_size);
    if(res) {
        char info[128];
        sprintf(info,"can not truncate file");
        throw std::runtime_error(info);
    }
}

bool UnixFileSystem::DirectoryExists(const std::string &directory) {
    auto res = access(directory.c_str(),F_OK);
    if(res)
        return false;
    struct stat info{};
    stat(directory.c_str(),&info);
    return S_ISDIR(info.st_mode);
}

void UnixFileSystem::CreateDirectory(const std::string &directory) {
    if(DirectoryExists(directory))
        return;
    auto res = mkdir(directory.c_str(),0755);
    if(res) {
        char info[128];
        sprintf(info,"can not create directory %s",directory.c_str());
        throw std::runtime_error(info);
    }
}

bool UnixFileSystem::FileExists(const std::string &filename) {
    return access(filename.c_str(),F_OK) == 0;
}

void UnixFileSystem::RemoveFile(const std::string &filename) {
    auto res = unlink(filename.c_str());
    if(res) {
        char info[128];
        sprintf(info,"can not remove file %s",filename.c_str());
        throw std::runtime_error(info);
    }
}

void UnixFileSystem::FileSync(FileHandle &handle) {
    auto res = fsync(handle.fd);
    if(res) {
        char info[128];
        sprintf(info,"can not sync file");
        throw std::runtime_error(info);
    }
}