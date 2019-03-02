#include "cqfoundation.lua.hh"
#include "cqbridge.hh"

CQ_C_LINK void CQ_Logger_info(CQBridgeValue message, CQBridgeValue file, CQBridgeValue line);
CQ_C_LINK void CQ_Logger_error(CQBridgeValue message, CQBridgeValue file, CQBridgeValue line);

static int Logger_info(lua_State *lua) {
    const char *a = luaL_checkstring(lua, 2);
    const char *b = luaL_checkstring(lua, 3);
    int32_t c = (int32_t)luaL_checkinteger(lua, 4);
    
    CQBridgeValue aa = CQBridgeCreateString(a, (int32_t)strlen(a));
    CQBridgeValue bb = CQBridgeCreateString(b, (int32_t)strlen(b));
    CQBridgeValue cc = CQBridgeCreateInt32(c);
    CQ_Logger_info(aa, bb, cc);
    CQBridgeRelease(aa);
    CQBridgeRelease(bb);
    CQBridgeRelease(cc);
    
    return 0;
}

static int Logger_error(lua_State *lua) {
    const char *a = luaL_checkstring(lua, 2);
    const char *b = luaL_checkstring(lua, 3);
    int32_t c = (int32_t)luaL_checkinteger(lua, 4);
    
    CQBridgeValue aa = CQBridgeCreateString(a, (int32_t)strlen(a));
    CQBridgeValue bb = CQBridgeCreateString(b, (int32_t)strlen(b));
    CQBridgeValue cc = CQBridgeCreateInt32(c);
    CQ_Logger_error(aa, bb, cc);
    CQBridgeRelease(aa);
    CQBridgeRelease(bb);
    CQBridgeRelease(cc);
    
    return 0;
}

static const struct luaL_Reg LoggerFunctions[] = {
    {"info", Logger_info},
    {"error", Logger_error},
    {nullptr, nullptr}
};

void CQFoundationOpenLuaLibrary(lua_State *lua) {
    luaL_dostring(lua, "CQLogger = extends(CQObject, {})");
    lua_getglobal(lua, "CQLogger");
    luaL_setfuncs(lua, LoggerFunctions, 0);
}
