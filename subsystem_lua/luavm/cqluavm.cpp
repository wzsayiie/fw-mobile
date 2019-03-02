#include "cqluavm.hh"
#include "cqextension.lua.hh"
#include "cqfoundation.lua.hh"
#include "cqlogger.hh"
#include "lua.hpp"
#include <unistd.h>

static lua_State *sLua = nullptr;

void CQLuaVMOpen(const std::string &path) {
    CQLuaVMClose();
    
    chdir(path.c_str());
    
    sLua = luaL_newstate();
    luaL_openlibs(sLua);
    CQLuaVMDoString("package.cpath = ''");
    CQLuaVMDoString("package.path = '?.lua'");
    CQLuaVMDoString("require 'CQRUNTIME'");
    
    CQExtensionOpenLuaLibrary(sLua);
    CQFoundationOpenLuaLibrary(sLua);
}

void CQLuaVMClose() {
    if (sLua != nullptr) {
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
    
    E("LUA RUNTIME ERROR:\n%s", ret);
    
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
        E("LUA SYNTAX ERROR:\n%s", info);
        return;
    }
    
    //execute
    int tracebackFuncIndex = lua_gettop(sLua) - 1;
    lua_pcall(sLua, 0, 0, tracebackFuncIndex);
}
