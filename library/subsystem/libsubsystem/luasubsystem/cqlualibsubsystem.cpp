#include "cqlualibsubsystem.h"
#include "cqsubsystemarche.h"

static int32_t cq_subsystem_start(lua_State *state) {
    cq_subsystem_start();
    return cq_lua_return_void(state);
}

static int32_t cq_subsystem_stop(lua_State *state) {
    cq_subsystem_stop();
    return cq_lua_return_void(state);
}

void cq_lua_load_lib_subsystem() {
    
#define register_func(name) cq_lua_register_func(#name, name)
    
    register_func(cq_subsystem_start);
    register_func(cq_subsystem_stop );
}
