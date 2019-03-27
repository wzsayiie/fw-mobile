#include "cqluavm.hh"
#include "cqfoundationlua.hh"
#include "cqlogger.hh"
#include "lua.hpp"
#include <unistd.h>

static lua_State *sLua = nullptr;

void CQLuaVMOpen(const std::string &path) {
    CQLuaVMClose();
    
    I("Lua VM: startup");
    
    chdir(path.c_str());
    
    sLua = luaL_newstate();
    luaL_openlibs(sLua);
    CQLuaVMDoString("package.cpath = ''");
    CQLuaVMDoString("package.path = '?.lua'");
    CQLuaVMDoString("require 'CQRUNTIME'");
    
    CQFoundationOpenLuaLibrary(sLua);
}

void CQLuaVMClose() {
    if (sLua != nullptr) {
        I("Lua VM: shoutdown");
        lua_close(sLua);
        sLua = nullptr;
    }
}

static int CQLuaVMTraceback(lua_State *lua) {
    
    lua_getglobal(lua, "debug");
    lua_getfield(lua, -1, "traceback");
    lua_pushvalue(lua, 1);
    lua_pushinteger(lua, 2);
    lua_call(lua, 2, 1);
    const char *ret = lua_tostring(lua, -1);
    
    E("lua runtime error:\n%s", ret);
    
    return 1;
}

void CQLuaVMDoString(const std::string &source) {
    if (sLua == nullptr) {
        return;
    }
    
    //trackback function
    lua_pushcfunction(sLua, CQLuaVMTraceback);
    
    //load
    int error = luaL_loadstring(sLua, source.c_str());
    if (error) {
        const char *info = lua_tostring(sLua, -1);
        E("lua syntax error:\n%s", info);
        return;
    }
    
    //execute
    int tracebackFuncIndex = lua_gettop(sLua) - 1;
    lua_pcall(sLua, 0, 0, tracebackFuncIndex);
}
