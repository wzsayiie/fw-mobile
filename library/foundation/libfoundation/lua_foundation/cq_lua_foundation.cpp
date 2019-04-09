#include "cq_lua_foundation.h"
#include "cq_log.h"
#include "lua.hpp"

static int log_info(lua_State *state) {
    
    const char *file = luaL_checkstring (state, 1);
    long long   line = luaL_checkinteger(state, 2);
    const char *text = luaL_checkstring (state, 3);
    
    cq_log_info(file, (int32_t)line, text);
    
    return 0;
}

static int log_error(lua_State *state) {
    
    const char *file = luaL_checkstring (state, 1);
    long long   line = luaL_checkinteger(state, 2);
    const char *text = luaL_checkstring (state, 3);
    
    cq_log_error(file, (int32_t)line, text);
    
    return 0;
}

static const struct luaL_Reg functions[] = {
    {"cq_log_info" , log_info },
    {"cq_log_error", log_error},
    {nullptr, nullptr}
};

static const char *source = R"lua(
-----------------------------------------------------------------------
function cq_string_format(format, args)
    local okay, text = pcall(string.format, format, table.unpack(args))
    if okay then
        return text
    else
        return "FORMAT EXCEPTION"
    end
end

function I(format, ...)
    local text = cq_string_format(format, {...})
    cq_log_info("", 0, text)
end

function E(format, ...)
    local text = cq_string_format(format, {...})
    cq_log_error("", 0, text)
end
-----------------------------------------------------------------------
)lua";

void cq_lua_foundation_open(void *lua_state, void (*execute)(const char *)) {
    if (lua_state != nullptr) {
        lua_getglobal((lua_State *)lua_state, "_G");
        luaL_setfuncs((lua_State *)lua_state, functions, 0);
    }
    if (execute != nullptr) {
        execute(source);
    }
}
