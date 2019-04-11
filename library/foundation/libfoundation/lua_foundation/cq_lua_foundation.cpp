#include "cq_lua_convention.h"
#include "cq_log.h"

CQ_LUA_FUNC(cq_log_info)(lua_State *state) {
    
    const char *file = cq_lua_check_string(state, 1);
    int32_t     line = cq_lua_check_int32 (state, 2);
    const char *text = cq_lua_check_string(state, 3);
    
    cq_log_info(file, line, text);
    
    return 0;
}

CQ_LUA_FUNC(cq_log_error)(lua_State *state) {
    
    const char *file = cq_lua_check_string(state, 1);
    int32_t     line = cq_lua_check_int32 (state, 2);
    const char *text = cq_lua_check_string(state, 3);
    
    cq_log_error(file, line, text);
    
    return 0;
}

CQ_LUA_STRING(get_source)() {
    const char *source = nullptr;
    #include "cq_lua_foundation.lua.h"
    return source;
}
