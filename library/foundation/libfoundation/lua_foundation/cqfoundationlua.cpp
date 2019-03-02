#include "cqfoundationlua.hh"
#include "cqbridgelua.hh"

CQ_C_LINK void CQ_Logger_info(CQBridgeValue message, CQBridgeValue file, CQBridgeValue line);
CQ_C_LINK void CQ_Logger_error(CQBridgeValue message, CQBridgeValue file, CQBridgeValue line);

static int Logger_info(lua_State *lua) {
    CQBridgeValue aa = CQBridgeLua<std::string>::create(lua, 2);
    CQBridgeValue bb = CQBridgeLua<std::string>::create(lua, 3);
    CQBridgeValue cc = CQBridgeLua<int32_t>::create(lua, 4);
    CQ_Logger_info(aa, bb, cc);
    CQBridgeRelease(aa);
    CQBridgeRelease(bb);
    CQBridgeRelease(cc);
    
    return 0;
}

static int Logger_error(lua_State *lua) {
    CQBridgeValue aa = CQBridgeLua<std::string>::create(lua, 2);
    CQBridgeValue bb = CQBridgeLua<std::string>::create(lua, 3);
    CQBridgeValue cc = CQBridgeLua<int32_t>::create(lua, 4);
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
