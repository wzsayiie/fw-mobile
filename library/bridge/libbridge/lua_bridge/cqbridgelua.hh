#pragma once

#include "cqbridgecore.h"
#include "lua.hpp"
#include <string>

template<class T> struct CQBridgeLua;

template<> struct CQBridgeLua<std::string> {
    static CQBridgeValue create(lua_State *lua, int index) {
        const char *raw = luaL_checkstring(lua, index);
        auto len = (int32_t)strlen(raw);
        return CQBridgeCreateString(raw, len);
    }
};

template<> struct CQBridgeLua<int32_t> {
    static CQBridgeValue create(lua_State *lua, int index) {
        auto raw = (int32_t)luaL_checkinteger(lua, index);
        return CQBridgeCreateInt32(raw);
    }
};
