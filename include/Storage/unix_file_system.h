//
// Created by user on 4/23/24.
//

#ifndef STORAGE_UNIX_FILE_SYSTEM_H
#define STORAGE_UNIX_FILE_SYSTEM_H
#include "file_system.h"

class UnixFileSystem:public FileSystem{
public:
     std::unique_ptr <FileHandle> OpenFile(const std::string &path,int64_t flags) override;

    //从偏移量为location处读取bytes数据,等效于Seek(handle,location)后调用Read(handle,buffer,bytes);
    //如果未读取到足够byte，则抛出std::runtime_error
     void Read(FileHandle &handle, void *buffer, int64_t bytes, off_t location) override;

    //从偏移量为location处写入bytes数据,等效于Seek(handle,location)后调用Write(handle,buffer,bytes);
    //如果未写入足够byte，则抛出std::runtime_error
     void Write(FileHandle &handle, void *buffer, int64_t bytes, off_t location) override;

    //读取bytes字节数据到buffer
     int64_t Read(FileHandle &handle, void *buffer, int64_t bytes) override;

    //写入bytes字节数据到buffer
     int64_t Write(FileHandle &handle, void *buffer, int64_t bytes) override;

     int64_t GetFileSize(FileHandle &handle) override;

     time_t GetLastModifiedTime(FileHandle &handle) override;

     void Truncate(FileHandle &handle, int64_t new_size) override;

     bool DirectoryExists(const std::string &directory) override;

     void CreateDirectory(const std::string &directory) override;

     bool FileExists(const std::string &filename) override;

     void RemoveFile(const std::string &filename) override;

     void FileSync(FileHandle &handle) override;

    //设置文件偏移量位location
     void Seek(FileHandle &handle, off_t location) override;
    //获取当前文件偏移量
     off_t GetSeek(FileHandle &handle) override;

    //设置文件偏移量为0，等同于Seek(handle,0)
     void Reset(FileHandle &handle) override;};


#endif //STORAGE_UNIX_FILE_SYSTEM_H
