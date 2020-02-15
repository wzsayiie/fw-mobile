#include "cqlualibsubsystem.h"
#include "cqsubsystemarche.h"

static int32_t SubsystemStart(lua_State *state) {
    cq_subsystem_start();
    return cq_lua_return_void(state);
}

static int32_t SubsystemStop(lua_State *state) {
    cq_subsystem_stop();
    return cq_lua_return_void(state);
}

void cq_lua_load_lib_subsystem() {
    
#define register_func(name) cq_lua_register_func(nullptr, nullptr, #name, name)
    
    register_func(SubsystemStart);
    register_func(SubsystemStop );
}
