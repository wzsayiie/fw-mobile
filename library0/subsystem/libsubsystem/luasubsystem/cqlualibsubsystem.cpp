#include "cqlualibsubsystem.h"
#include "cqsubsystemarche.h"

static int32_t subsystem_start(lua_State *state) {
    cq_subsystem_start();
    return cq_lua_return_void(state);
}

static int32_t subsystem_stop(lua_State *state) {
    cq_subsystem_stop();
    return cq_lua_return_void(state);
}

void cq_lua_load_lib_subsystem() {
    
#define lua_func(name) cq_lua_register_function(nullptr, #name, name)
    
    lua_func(subsystem_start);
    lua_func(subsystem_stop );
}
