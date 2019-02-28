#include "cqluavm.hh"
#include "lua.hpp"

static std::string *sPath = nullptr;
static lua_State   *sLua  = nullptr;

void CQLuaVMOpen(const std::string &path) {
    CQLuaVMClose();
    
    sPath = new std::string(path);
    sLua  = luaL_newstate();
    
    luaL_openlibs(sLua);
    CQLuaVMDoString("package.path = '" + path + "/?.lua'");
    CQLuaVMDoFile("CQRUNTIME.lua");
}

void CQLuaVMClose() {
    if (sPath != nullptr) {
        delete sPath;
        sPath = nullptr;
    }
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

//    if (sLua != nullptr) {
//        std::string info;
//        info.append("lua runtime error:\n");
//        info.append(lua_tostring(lua, -1));
//        sLog(info);
//    }
    
    return 1;
}

void CQLuaVMDoFile(const std::string &fileName) {
    if (sLua == nullptr) {
        return;
    }
    if (sPath == nullptr) {
        return;
    }
    
    //trackback function
    lua_pushcfunction(sLua, CQLuaVMTraceback);
    
    //load
    std::string filePath = *sPath + "/" + fileName;
    int error = luaL_loadfile(sLua, filePath.c_str());
    if (error) {
//        if (sLog != nullptr) {
//            std::string info;
//            info.append("lua syntax error:\n");
//            info.append(lua_tostring(sLua, -1));
//            sLog(info);
//        }
        return;
    }
    
    //execute
    int tracebackFuncIndex = lua_gettop(sLua) - 1;
    lua_pcall(sLua, 0, 0, tracebackFuncIndex);
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
//        if (sLog != nullptr) {
//            std::string info;
//            info.append("lua syntax error:\n");
//            info.append(lua_tostring(sLua, -1));
//            sLog(info);
//        }
        return;
    }
    
    //execute
    int tracebackFuncIndex = lua_gettop(sLua) - 1;
    lua_pcall(sLua, 0, 0, tracebackFuncIndex);
}
