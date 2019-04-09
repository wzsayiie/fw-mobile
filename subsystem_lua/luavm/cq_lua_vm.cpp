#include "cq_lua_vm.h"
#include "cqlog.hh"
#include "lua.hpp"

# ifdef _WIN32
#   include <windows.h>
# else
#   include <unistd.h>
# endif

static lua_State *_lua_state = nullptr;

void cq_lua_vm_open(const char *directory_path) {
    I("lua vm: open '%s'", directory_path);
    cq_lua_vm_close();
    
    _lua_state = luaL_newstate();
    luaL_openlibs(_lua_state);
    
#ifdef _WIN32
    SetCurrentDirectoryA(directory_path);
#else
    chdir(directory_path);
#endif
    cq_lua_vm_do_string("package.cpath = ''");
    cq_lua_vm_do_string("package.path = '?.lua'");
}

void cq_lua_vm_close() {
    if (_lua_state != nullptr) {
        I("lua vm: close");
        lua_close(_lua_state);
        _lua_state = nullptr;
    }
}

static int cq_lua_vm_traceback(lua_State *state) {
    
    lua_getglobal(state, "debug");
    lua_getfield(state, -1, "traceback");
    lua_pushvalue(state, 1);
    lua_pushinteger(state, 2);
    lua_call(state, 2, 1);
    const char *info = lua_tostring(state, -1);
    
    E("lua vm: runtime error:\n%s", info);
    
    return 1;
}

void cq_lua_vm_do_string(const char *source) {
    if (_lua_state == nullptr) {
        return;
    }
    
    //trackback function
    lua_pushcfunction(_lua_state, cq_lua_vm_traceback);
    
    //load
    int error = luaL_loadstring(_lua_state, source);
    if (error) {
        const char *info = lua_tostring(_lua_state, -1);
        E("lua vm: syntax error:\n%s", info);
        return;
    }
    
    //execute
    int traceback = lua_gettop(_lua_state) - 1;
    lua_pcall(_lua_state, 0, 0, traceback);
}
