#include "cqluavm.h"
#include "cqfoundation.hh"
#include "lua.hpp"

static lua_State *_lua_state = nullptr;

static void register_func(const char *name, int32_t (*func)(lua_State *)) {
    if (_lua_state == nullptr) {
        I("lua vm: try register function but lua state was not initialized");
        return;
    }
    if (cq_string_null_or_emptry(name)) {
        I("lua vm: try register function but the name specified is empty");
        return;
    }
    if (func == nullptr) {
        I("lua vm: try register function but the c pointer specified is empty");
        return;
    }
    
    lua_register(_lua_state, name, func);
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
    if (_lua_state == nullptr) {
        I("lua vm: try do lua string but lua state was not initialized");
        return;
    }
    if (cq_string_null_or_emptry(code)) {
        I("lua vm: try do lua string but the code string is emptry");
        return;
    }
    
    //trackback function
    lua_pushcfunction(_lua_state, traceback);
    
    //load
    int error = luaL_loadstring(_lua_state, code);
    if (error) {
        const char *info = lua_tostring(_lua_state, -1);
        E("lua vm: syntax error:\n%s", info);
        return;
    }
    
    //execute
    int traceback = lua_gettop(_lua_state) - 1;
    lua_pcall(_lua_state, 0, 0, traceback);
}

static int64_t     check_integer(lua_State *s, int32_t i) {return luaL_checkinteger(s, i);}
static double      check_double (lua_State *s, int32_t i) {return luaL_checknumber (s, i);}
static const char *check_string (lua_State *s, int32_t i) {return luaL_checkstring (s, i);}

static void push_bool   (lua_State *s, bool        v) {lua_pushboolean(s, v);}
static void push_integer(lua_State *s, int64_t     v) {lua_pushinteger(s, v);}
static void push_double (lua_State *s, double      v) {lua_pushnumber (s, v);}
static void push_string (lua_State *s, const char *v) {lua_pushstring (s, v);}

void cq_lua_open_vm() {
    I("lua vm: open");
    
    cq_lua_close_vm();
    
    //new lua vm
    _lua_state = luaL_newstate();
    luaL_openlibs(_lua_state);

    //register handlers
    _cq_lua_set_register_func_handler(register_func);
    _cq_lua_set_do_string_handler(do_string);
    
    _cq_lua_set_check_integer_handler(check_integer);
    _cq_lua_set_check_double_handler (check_double );
    _cq_lua_set_check_string_handler (check_string );
    
    _cq_lua_set_push_bool_handler   (push_bool   );
    _cq_lua_set_push_integer_handler(push_integer);
    _cq_lua_set_push_double_handler (push_double );
    _cq_lua_set_push_string_handler (push_string );
}

void cq_lua_close_vm() {
    if (_lua_state == nullptr) {
        return;
    }
    
    I("lua vm: close");
    
    //disable third library
    _cq_lua_set_register_func_handler(nullptr);
    _cq_lua_set_do_string_handler(nullptr);
    
    _cq_lua_set_check_integer_handler(nullptr);
    _cq_lua_set_check_double_handler (nullptr);
    _cq_lua_set_check_string_handler (nullptr);
    
    _cq_lua_set_push_integer_handler(nullptr);
    _cq_lua_set_push_double_handler (nullptr);
    _cq_lua_set_push_string_handler (nullptr);
    
    //delete lua vm
    lua_close(_lua_state);
    _lua_state = nullptr;
}
