#include "cqluasource.h"
#include "cqcppbasis.hh"
#include "cqfoundation.hh"

static const char *sources[] = {
//use generate.sh (or generate.bat) to create GENERATED_LUA.
#include "../../GENERATED_LUA/GENERATED_LUA"
nullptr, nullptr,
};

void cq_lua_source_update(const char *directory_path) {
    I("lua source: path '%s'", directory_path);
    
    if (directory_path == nullptr) {
        return;
    }
    
    const char **file_name = sources + 0;
    const char **file_mass = sources + 1;
    while (*file_name != nullptr && *file_mass != nullptr) {
        
        string file_path;
        file_path.append(directory_path);
        file_path.append("/");
        file_path.append(*file_name);
        
        if (FILE *writer = fopen(file_path.c_str(), "wb")) {
            I("lua source: update file '%s'", *file_name);
            size_t file_size = strlen(*file_mass);
            fwrite(*file_mass, 1, file_size, writer);
            fclose(writer);
        } else {
            I("lua source: failed to write '%s'", *file_name);
        }
        
        file_name += 2;
        file_mass += 2;
    }
}
