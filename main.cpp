#include "file_system.h"
static constexpr char tempfile[] = "/dev/shm/temp";
int main() {
    auto& fs = FileSystem::Get();
    auto file = fs.OpenFile(tempfile,FileOpenFlags::FILE_FLAGS_READ_AND_WRITE
                        | FileOpenFlags::FILE_FLAGS_CREATE_NEW);
    file->Write((void*)tempfile,sizeof(tempfile),0);

    return 0;
}
/*
char sql[] = "select * from test where id >= 1200 && score * (id + value) >= 0x15000;";
extern void *ParseAlloc(void*(*malloc)(size_t) );
extern void ParseFree(void *pParser, void(*free)(void*) );
extern void Parse(void *pParser, int tokenCode,Lexer::Token* token);
extern void ParseTrace(FILE *stream, char *zPrefix);
std::array<int,5> num;
*/