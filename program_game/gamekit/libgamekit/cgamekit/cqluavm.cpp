#include "cqluavm.h"
#include "cqfoundation.hh"
#include "lua.hpp"

# if CQ_ON_WINDOWS
#   include <Winbase.h>
# else
#   include <unistd.h>
# endif

static lua_State *_state = nullptr;

static void register_func(const char *name, int32_t (*func)(lua_State *)) {
    if (_state == nullptr) {
        I("lua vm: register function but vm was not initialized");
        return;
    }
    if (cq_str_empty(name)) {
        I("lua vm: register function but the name is empty");
        return;
    }
    if (func == nullptr) {
        I("lua vm: register function but the c pointer is empty");
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
    
    E("lua vm: runtime error:\n%s", info);
    
    return 1;
}

static void do_string(const char *code) {
    if (_state == nullptr) {
        I("lua vm: do string but vm was not initialized");
        return;
    }
    if (cq_str_empty(code)) {
        I("lua vm: do string but the code is emptry");
        return;
    }
    
    //trackback function
    lua_pushcfunction(_state, traceback);
    
    //load
    int error = luaL_loadstring(_state, code);
    if (error) {
        const char *info = lua_tostring(_state, -1);
        E("lua vm: syntax error:\n%s", info);
        return;
    }
    
    //execute
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

void cq_lua_open_vm(const char *directory) {
    I("lua vm: open");
    
    cq_lua_close_vm();
    
    //new vm
    _state = luaL_newstate();
    luaL_openlibs(_state);
    
    //change work directory. otherwise,
    //the file name specified by runtime error message is very long.
  #if CQ_ON_WINDOWS
    SetCurrentDirectoryA(directory);
  #else
    chdir(directory);
  #endif
    do_string("package.path  = '?.lua'");
    do_string("package.cpath = ''");

    //register handlers
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

void cq_lua_close_vm() {
    if (_state == nullptr) {
        return;
    }
    
    I("lua vm: close");
    
    //disable handlers
    _cq_lua_set_handlers(nullptr);
    
    //delete vm
    lua_close(_state);
    _state = nullptr;
}
