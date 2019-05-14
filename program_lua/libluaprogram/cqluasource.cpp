#include "cqluasource.h"
#include "cqfoundation.hh"
#include <algorithm>

static std::map<std::string, std::string> *get_script_sources() {
    static std::map<std::string, std::string> *map = nullptr;
    if (map != nullptr) {
        return map;
    }
    
    I("lua source: initialize sources");
    map = new std::map<std::string, std::string>;
    
    const char *sources[] = {
        //use script generate_lua(.bat) to create GENERATED_LUA.
        #include "../../GENERATED_LUA/GENERATED_LUA"
        nullptr, nullptr,
    };
    const char **name = sources + 0;
    const char **mass = sources + 1;
    for (; *name && *mass; name += 2, mass += 2) {
        
        //name should be "xx.lua".
        size_t name_size = strlen(*name);
        if (name_size <= 4) {
            continue;
        }
        
        std::string module;
        module.append(*name, name_size - 4);
        std::transform(module.begin(), module.end(), module.begin(), ::tolower);
        (*map)[module] = *mass;
        I("lua source: store module '%s'", module.data());
    }
    
    return map;
}

static std::set<std::string> *get_loaded_modules() {
    static std::set<std::string> *set = nullptr;
    if (set == nullptr) {
        set = new std::set<std::string>;
    }
    return set;
}

static int32_t require(lua_State *state) {
    
    const char *name = cq_lua_check_string(state, 1);
    if (cq_string_null_or_emptry(name)) {
        E("lua source: try load module but name specified is empty");
        return cq_lua_push_bool(state, false);
    }
    std::string module = name;
    std::transform(module.begin(), module.end(), module.begin(), ::tolower);
    
    auto loaded_modules = get_loaded_modules();
    if (loaded_modules->find(module) != loaded_modules->end()) {
        E("lua source: try load module '%s' but it's already loaded", module.data());
        return cq_lua_push_bool(state, false);
    }
    
    auto script_sources = get_script_sources();
    auto source = script_sources->find(module);
    if (source == script_sources->end()) {
        E("lua source: not found module '%s'", module.data());
        return cq_lua_push_bool(state, false);
    }
    
    loaded_modules->insert(module);
    cq_lua_do_string(source->second.data());
    return cq_lua_push_bool(state, true);
}

void cq_lua_run_scripts() {
    
    cq_lua_register_func("cq_require", require);
    
    auto script_sources = get_script_sources();
    auto source = script_sources->find("cqruntime");
    if (source != script_sources->end()) {
        I("lua source: run scripts");
        cq_lua_do_string(source->second.data());
    } else {
        E("lua source: not found runtime");
    }
}
