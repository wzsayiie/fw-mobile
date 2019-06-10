#include "cqlualibsubsystem.h"
#include "cqsubsystemarche.h"

static int32_t subsystem_start(lua_State *state) {
    cq_subsystem_start();
    return cq_lua_push_void(state);
}

static int32_t subsystem_stop(lua_State *state) {
    cq_subsystem_stop();
    return cq_lua_push_void(state);
}

void cq_lua_load_lib_subsystem() {
    cq_lua_register_func("cq_subsystem_start", subsystem_start);
    cq_lua_register_func("cq_subsystem_stop" , subsystem_stop );
}
