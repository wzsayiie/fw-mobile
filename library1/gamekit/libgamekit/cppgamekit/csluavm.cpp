#include "csluavm.hh"
#include "cqctool.hh"
#include "cqfoundation.hh"
#include "cqluabasis.h"
#include "lua.hpp"

# if CQ_ON_ANDROID
#   include <android/log.h>
# else
#   include <cstdio>
# endif

static lua_State *_state = nullptr;

static void register_func(const char *name, int32_t (*func)(lua_State *)) {
    if (_state == nullptr) {
        return;
    }
    if (cq_str_empty(name)) {
        return;
    }
    if (func == nullptr) {
        return;
    }
    
    lua_register(_state, name, func);
}

static int traceback(lua_State *state) {
    
    lua_getglobal(state, "debug");
    lua_getfield(state, -1, "traceback");
    lua_pushvalue(state, 1);
    lua_pushinteger(state, 2);
    lua_call(state, 2, 1);
    const char *info = lua_tostring(state, -1);
    
#if CQ_ON_ANDROID
    __android_log_print(ANDROID_LOG_ERROR, "lua", "lua vm: runtime error:\n%s", info);
#else
    fprintf(stderr, "lua vm: runtime error:\n%s", info);
#endif
    
    return 1;
}

static void do_string(const char *code) {
    if (_state == nullptr) {
        return;
    }
    if (cq_str_empty(code)) {
        return;
    }
    
    //trackback function.
    lua_pushcfunction(_state, traceback);
    
    //load.
    int error = luaL_loadstring(_state, code);
    if (error) {
        const char *info = lua_tostring(_state, -1);
#if CQ_ON_ANDROID
        __android_log_print(ANDROID_LOG_ERROR, "lua", "lua vm: syntax error:\n%s", info);
#else
        fprintf(stderr, "lua vm: syntax error:\n%s", info);
#endif
        return;
    }
    
    //execute.
    int traceback = lua_gettop(_state) - 1;
    lua_pcall(_state, 0, 0, traceback);
}

static int64_t check_integer(lua_State *s, int32_t i) {return luaL_checkinteger(s, i);}
static double  check_double (lua_State *s, int32_t i) {return luaL_checknumber (s, i);}

static const char *check_string(lua_State *state, int32_t indent) {
    return luaL_checkstring(state, indent);
}

static void push_bool   (lua_State *s, bool    v) {lua_pushboolean(s, v);}
static void push_integer(lua_State *s, int64_t v) {lua_pushinteger(s, v);}
static void push_double (lua_State *s, double  v) {lua_pushnumber (s, v);}

static void push_string(lua_State *state, const char *value) {
    lua_pushstring(state, value);
}

static void collectSubDirectories(std::vector<std::string> *added, const std::string &directory) {
    added->push_back(directory);
    
    auto items = cqFileManager::get()->contentsOfDirectoryAtPath(directory);
    for (auto &it : items) {
        std::string path = cqPathString::append(directory, it);
        if (cqFileManager::get()->directoryExists(path)) {
            collectSubDirectories(added, path);
        }
    }
}

void csLuaVM::open(const std::string &directory) {
    if (directory.empty()) {
        return;
    }
    
    csLuaVM::close();
    
    //new vm.
    _state = luaL_newstate();
    luaL_openlibs(_state);
    
    //set search path.
    std::string pathes; {
        std::vector<std::string> subDirectories;
        collectSubDirectories(&subDirectories, directory);
        for (auto &it : subDirectories) {
            if (!pathes.empty()) {
                pathes.append(";");
            }
            pathes.append(cqPathString::append(it, "?.lua"));
        }
    }
    do_string(("package.path = '" + pathes + "'").c_str());
    do_string("package.cpath = ''");
    
    //register handlers.
    _cq_lua_handlers handlers = {nullptr}; {
        handlers.register_func = register_func;
        handlers.do_string     = do_string    ;
        handlers.check_integer = check_integer;
        handlers.check_double  = check_double ;
        handlers.check_string  = check_string ;
        handlers.push_bool     = push_bool    ;
        handlers.push_integer  = push_integer ;
        handlers.push_double   = push_double  ;
        handlers.push_string   = push_string  ;
    }
    _cq_lua_set_handlers(&handlers);
}

void csLuaVM::close() {
    if (_state == nullptr) {
        return;
    }
    
    //disable handlers.
    _cq_lua_set_handlers(nullptr);
    
    //delete vm.
    lua_close(_state);
    _state = nullptr;
}
