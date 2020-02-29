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

struct lua_stack_guard {
    
    lua_stack_guard(lua_State *state) {
        _state = state;
        _top = state ? lua_gettop(state) : 0;
    }
    ~lua_stack_guard() {
        if (_state != nullptr) {
            lua_settop(_state, _top);
        }
    }
    
private:
    lua_State *_state;
    int _top;
};

static void add_global_tab(lua_State *state, const char *tab, const char *base) {
    lua_stack_guard gurad(state);
    
    //create table.
    if (cq_str_empty(tab)) {
        return;
    }
    
    lua_getglobal(state, tab);
    if (!lua_isnil(state, -1)) {
        //the table already exists.
        return;
    }
    
    lua_newtable(state);
    lua_setglobal(state, tab);
    
    //set meta table.
    if (cq_str_empty(base)) {
        return;
    }
    
    lua_getglobal(state, tab);
    
    lua_newtable(state);
    lua_pushstring(state, "__index");
    lua_getglobal(state, base);
    lua_settable(state, -3);
    
    lua_setmetatable(state, -2);
}

static void add_table_func(lua_State *state, const char *tab, const char *func, lua_CFunction ptr) {
    lua_stack_guard gurad(state);
    
    lua_getglobal(state, tab);
    
    luaL_Reg list[] = {func, ptr, nullptr, nullptr};
    luaL_setfuncs(state, list, 0);
}

static lua_State *_state = nullptr;

static void register_tab(const char *tab, const char *base) {
    if (_state == nullptr) {
        return;
    }
    
    if (!cq_str_empty(tab)) {
        add_global_tab(_state, tab, base);
    }
}

static void register_func(const char *tab, const char *func, lua_CFunction ptr) {
    if (_state == nullptr) {
        return;
    }
    if (cq_str_empty(func) || ptr == nullptr) {
        return;
    }
    
    if (!cq_str_empty(tab)) {
        //register a class member function.
        add_global_tab(_state, tab, nullptr);
        add_table_func(_state, tab, func, ptr);
    } else {
        //register a global function.
        lua_register(_state, func, ptr);
    }
}

static int traceback(lua_State *state) {
    lua_stack_guard gurad(state);
    
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
    lua_stack_guard gurad(_state);
    
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
    lua_pcall(_state, 0, 0, -2);
}

static int64_t     check_integer(lua_State *s, int32_t i) {return luaL_checkinteger(s, i);}
static double      check_double (lua_State *s, int32_t i) {return luaL_checknumber (s, i);}
static const char *check_string (lua_State *s, int32_t i) {return luaL_checkstring (s, i);}

static cq_obj *check_object(lua_State *state, int32_t index) {
    lua_stack_guard guard(state);
    
    if (!lua_istable(state, index)) {
        return nullptr;
    }
    
    lua_getfield(state, index, "cq_obj");
    if (!lua_isinteger(state, -1)) {
        return nullptr;
    }
    
    lua_Integer raw = lua_tointeger(state, -1);
    return (cq_obj *)raw;
}

static cq_int64s *check_integers(lua_State *state, int32_t index) {
    lua_stack_guard guard(state);
    
    if (!lua_istable(state, index)) {
        return cq_store_c_int64s(nullptr, nullptr);
    }
    
    std::vector<int64_t> object;
    
    lua_pushnil(state); //lua_next() will pop the last key at the first.
    while (lua_next(state, index)) {
        int64_t it = lua_tonumber(state, -1);
        object.push_back(it);
        
        lua_pop(state, 1);
    }
    
    return cq_store_cpp_int64s(object);
}

static cq_strings *check_strings(lua_State *state, int32_t index) {
    lua_stack_guard guard(state);
    
    if (!lua_istable(state, index)) {
        return cq_store_c_strings(nullptr, nullptr);
    }
    
    std::vector<std::string> object;
    
    lua_pushnil(state);
    while (lua_next(state, index)) {
        const char *it = lua_tostring(state, -1);
        object.push_back(it);
        
        lua_pop(state, 1);
    }
    
    return cq_store_cpp_strings(object);
}

static cq_ss_map *check_ss_table(lua_State *state, int32_t index) {
    lua_stack_guard guard(state);
    
    if (!lua_istable(state, index)) {
        return cq_store_c_ss_map(nullptr, nullptr);
    }
    
    std::map<std::string, std::string> object;
    
    lua_pushnil(state);
    while (lua_next(state, index)) {
        const char *val = lua_tostring(state, -1);
        const char *key = lua_tostring(state, -2);
        object[key] = val;
        
        lua_pop(state, 1);
    }
    
    return cq_store_cpp_ss_map(object);
}

static void push_bool   (lua_State *s, bool        v) {lua_pushboolean(s, v);}
static void push_integer(lua_State *s, int64_t     v) {lua_pushinteger(s, v);}
static void push_double (lua_State *s, double      v) {lua_pushnumber (s, v);}
static void push_string (lua_State *s, const char *v) {lua_pushstring (s, v);}

static int32_t obj_gc(lua_State *state) {
    lua_stack_guard guard(state);
    
    lua_getfield(state, -1, "cq_obj");
    lua_Integer raw = lua_tointeger(state, -1);
    cq_release_obj((cq_obj *)raw);
    
    return 0;
}

static void push_object(lua_State *state, cq_obj *value) {
    if (value == nullptr) {
        lua_pushnil(state);
        return;
    }
    
    cq_retain_obj(value);
    
    lua_newtable(state);
    
    //use lua_Integer to hold the c pointer.
    static_assert(sizeof(lua_Integer) >= sizeof(cq_obj *), "");
    lua_pushstring(state, "cq_obj");
    lua_pushinteger(state, (lua_Integer)value);
    lua_settable(state, -3);
    
    //set meta table:
    lua_newtable(state);
    
    //assign __index.
    const char *cls = cq_obj_cls(value);
    if (!cq_str_empty(cls)) {
        lua_pushstring(state, "__index");
        lua_getglobal(state, cls);
        if (lua_istable(state, -1)) {
            lua_settable(state, -3);
        } else {
            lua_pop(state, 2);
        }
    }
    
    //assign __gc.
    lua_pushstring(state, "__gc");
    lua_pushcfunction(state, obj_gc);
    lua_settable(state, -3);
    
    lua_setmetatable(state, -2);
}

static void push_integers(lua_State *state, cq_int64s_sender send, cq_int64s *value) {
    std::vector<int64_t> object = cq_cpp_int64s_from(send, value);
    
    lua_newtable(state);
    
    int index = 1; //lua table's index begins with 1.
    for (auto &it : object) {
        lua_pushnumber(state, index++);
        lua_pushnumber(state, it);
        lua_settable(state, -3);
    }
}

static void push_strings(lua_State *state, cq_strings_sender send, cq_strings *value) {
    std::vector<std::string> object = cq_cpp_strings_from(send, value);
    
    lua_newtable(state);
    
    int index = 1;
    for (auto &it : object) {
        lua_pushnumber(state, index++);
        lua_pushstring(state, it.c_str());
        lua_settable(state, -3);
    }
}

static void push_ss_table(lua_State *state, cq_ss_map_sender send, cq_ss_map *value) {
    std::map<std::string, std::string> object = cq_cpp_ss_map_from(send, value);
    
    lua_newtable(state);
    
    for (auto &cp : object) {
        lua_pushstring(state, cp.first .c_str());
        lua_pushstring(state, cp.second.c_str());
        lua_settable(state, -3);
    }
}

static void collectSubDirectories(std::vector<std::string> *added, const std::string &directory) {
    added->push_back(directory);
    
    auto items = cqFileManager::get()->contentsOfDirectoryAtPath(directory, nullptr);
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
        handlers.register_tab   = register_tab  ;
        handlers.register_func  = register_func ;
        handlers.do_string      = do_string     ;
        
        handlers.check_integer  = check_integer ;
        handlers.check_double   = check_double  ;
        handlers.check_string   = check_string  ;
        handlers.check_object   = check_object  ;
        handlers.check_integers = check_integers;
        handlers.check_strings  = check_strings ;
        handlers.check_ss_table = check_ss_table;
        
        handlers.push_bool      = push_bool     ;
        handlers.push_integer   = push_integer  ;
        handlers.push_double    = push_double   ;
        handlers.push_string    = push_string   ;
        handlers.push_object    = push_object   ;
        handlers.push_integers  = push_integers ;
        handlers.push_strings   = push_strings  ;
        handlers.push_ss_table  = push_ss_table ;
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
