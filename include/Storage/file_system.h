//
// Created by user on 4/23/24.
//

#ifndef STORAGE_FILE_SYSTEM_H
#define STORAGE_FILE_SYSTEM_H
#include <utility>

#include "../../utility.h"

class FileSystem;
class FileHandle {
public:
    FileHandle(FileSystem &file_system, std::string path,int fd):
    file_system(file_system),path(std::move(path)),fd(fd){}
    FileHandle(const FileHandle &) = delete;
    ~FileHandle(){Close();}

    int64_t Read(void *buffer, int64_t bytes);

    int64_t Write(void *buffer, int64_t bytes);

    void Read(void *buffer, int64_t bytes, off_t location);

    void Write(void *buffer, int64_t bytes, off_t location);

    void Seek(off_t location);

    void Reset();

    off_t GetSeek();

    void Sync();

    void Truncate(int64_t new_size);


    size_t GetFileSize();


    void Close() const;

    [[nodiscard]] std::string GetPath() const {
        return path;
    }

    template<class TARGET>
    TARGET &Cast() {
        DynamicCastCheck<TARGET>(this);
        return reinterpret_cast<TARGET &>(*this);
    }

    template<class TARGET>
    const TARGET &Cast() const {
        DynamicCastCheck<TARGET>(this);
        return reinterpret_cast<const TARGET &>(*this);
    }

    FileSystem &file_system;
    std::string path;
    int fd;
};
class FileOpenFlags{
public:
    static constexpr int64_t FILE_FLAGS_READ = int64_t(1 << 0);
    static constexpr int64_t FILE_FLAGS_WRITE = int64_t(1 << 1);
    static constexpr int64_t FILE_FLAGS_READ_AND_WRITE = int64_t(1 << 2);
    static constexpr int64_t FILE_FLAGS_DIRECT_IO = int64_t(1 << 3);
    static constexpr int64_t FILE_FLAGS_CREATE = int64_t(1 << 4);
    static constexpr int64_t FILE_FLAGS_CREATE_NEW = int64_t(1 << 5);
    static constexpr int64_t FILE_FLAGS_APPEND = int64_t(1 << 6);
};

class FileSystem {
public:
    static FileSystem& Get();
    FileSystem() = default;
    FileSystem(const FileSystem &) = delete;
    virtual std::unique_ptr <FileHandle> OpenFile(const std::string &path,int64_t flags);

    //从偏移量为location处读取bytes数据,等效于Seek(handle,location)后调用Read(handle,buffer,bytes);
    //如果未读取到足够byte，则抛出std::runtime_error
    virtual void Read(FileHandle &handle, void *buffer, int64_t bytes, off_t location);

    //从偏移量为location处写入bytes数据,等效于Seek(handle,location)后调用Write(handle,buffer,bytes);
    //如果未写入足够byte，则抛出std::runtime_error
    virtual void Write(FileHandle &handle, void *buffer, int64_t bytes, off_t location);

    //读取bytes字节数据到buffer
    virtual int64_t Read(FileHandle &handle, void *buffer, int64_t bytes);

    //写入bytes字节数据到buffer
    virtual int64_t Write(FileHandle &handle, void *buffer, int64_t bytes);

    virtual int64_t GetFileSize(FileHandle &handle);

    virtual time_t GetLastModifiedTime(FileHandle &handle);

    virtual void Truncate(FileHandle &handle, int64_t new_size);

    virtual bool DirectoryExists(const std::string &directory);

    virtual void CreateDirectory(const std::string &directory);

    virtual bool FileExists(const std::string &filename);

    virtual void RemoveFile(const std::string &filename);

    virtual void FileSync(FileHandle &handle);

    //设置文件偏移量位location
    virtual void Seek(FileHandle &handle, off_t location);
    //获取当前文件偏移量
    virtual off_t GetSeek(FileHandle &handle);

    //设置文件偏移量为0，等同于Seek(handle,0)
    virtual void Reset(FileHandle &handle);

    static void SetWorkingDirectory(const std::string &path);

    static std::string GetWorkingDirectory();

    static std::string GetHomeDirectory();
    //将a和b进行拼接
    static std::string JoinPath(const std::string &a,const std::string &b);
    //检查文件路径是否为绝对路径(是否以路径分隔符开头)
    static bool IsPathAbsolute(const std::string &path);

    //提取包含后缀的文件名 (e.g if the input is lib/example.dll the name is 'example.dll')
    static std::string ExtractName(const std::string &path);

    //! Returns the value of an environment variable - or the empty std::string if it is not set
    static std::string GetEnvVariable(const std::string &name);
public:
    template<class TARGET>
    TARGET &Cast() {
        DynamicCastCheck<TARGET>(this);
        return reinterpret_cast<TARGET &>(*this);
    }

    template<class TARGET>
    const TARGET &Cast() const {
        DynamicCastCheck<TARGET>(this);
        return reinterpret_cast<const TARGET &>(*this);
    }
};


#endif //STORAGE_FILE_SYSTEM_H
