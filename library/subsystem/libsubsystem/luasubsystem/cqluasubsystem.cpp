#include "cqluasubsystem.h"
#include "cqsubsystemarche.h"

static int32_t subsystem_start(lua_State *state) {
    const char *name = cq_lua_check_string(state, 1);
    cq_subsystem_start(name);
    return 0;
}

static int32_t subsystem_stop(lua_State *state) {
    const char *name = cq_lua_check_string(state, 1);
    cq_subsystem_stop(name);
    return 0;
}

void cq_lua_load_lib_subsystem() {
    
    cq_lua_register_func("cq_subsystem_start", subsystem_start);
    cq_lua_register_func("cq_subsystem_stop" , subsystem_stop );
    
    const char *source = nullptr;
    #include "cqluasubsystem_lua.h"
    cq_lua_do_string(source);
}
