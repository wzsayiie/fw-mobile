#include "cqluasource.hh"
#include "cqlogger.hh"

static const char *LUA_SOURCES[] = {
//use generate.sh (or generate.bat) to create GENERATED_LUA.
#include "../../GENERATED_LUA/GENERATED_LUA"
nullptr, nullptr,
};

void CQLuaSourceUpdate(const std::string &path) {
    I("Lua VM: lua path '%s'", path.c_str());
    
    const char **fileName    = LUA_SOURCES + 0;
    const char **fileContent = LUA_SOURCES + 1;
    
    while (*fileName != nullptr && *fileContent != nullptr) {
        std::string filePath = path + "/" + *fileName;
        
        FILE *fileWriter = fopen(filePath.c_str(), "wb");
        if (fileWriter != nullptr) {
            I("Lua VM: update file '%s'", *fileName);
            size_t fileSize = strlen(*fileContent);
            fwrite(*fileContent, 1, fileSize, fileWriter);
            fclose(fileWriter);
        } else {
            I("Lua VM: failed to update file '%s'", *fileName);
        }
        
        fileName += 2;
        fileContent += 2;
    }
}
