#include "luasource.hh"
#include "cqctool.hh"
#include "cqfoundation.hh"

static const char **source() {
//    const char *holder = nullptr;
//    #define LUA holder =
//
//    static const char *list[] = {
//        //use script generate_lua(.bat) to create GENERATED_LUA.
//        #include "../GENERATED_LUA/GENERATED_LUA"
//        nullptr, nullptr
//    };
//    return list;
    return nullptr;
}

void LuaSource::update(const std::string &directory) {
    I("lua source: update lua file");
    
    for (auto it = source(); it[0] && it[1]; it += 2) {
        const char *name = it[0];
        const char *text = it[1];
        
        std::string path = cqPathString::append(directory, name);
        if (cqData::writeFile(path, text, strlen(text))) {
            I("lua source: update '%s'", name);
        } else {
            I("lua source: failed to update '%s'", name);
        }
    }
}
