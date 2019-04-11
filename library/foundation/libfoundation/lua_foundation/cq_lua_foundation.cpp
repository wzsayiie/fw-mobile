#include "cq_lua_convention.h"
#include "cq_lua_foundation.h"
#include "cq_log.h"

static int32_t log_info(lua_State *state) {
    
    const char *file = cq_lua_check_string(state, 1);
    int32_t     line = cq_lua_check_int32 (state, 2);
    const char *text = cq_lua_check_string(state, 3);
    
    cq_log_info(file, line, text);
    
    return 0;
}

static int32_t log_error(lua_State *state) {
    
    const char *file = cq_lua_check_string(state, 1);
    int32_t     line = cq_lua_check_int32 (state, 2);
    const char *text = cq_lua_check_string(state, 3);
    
    cq_log_error(file, line, text);
    
    return 0;
}

void cq_lua_load_lib_foundation() {
    
    cq_lua_register_func("cq_log_info" , log_info );
    cq_lua_register_func("cq_log_error", log_error);
    
    const char *source = nullptr;
    #include "cq_lua_foundation.lua.h"
    cq_lua_do_string(source);
}
