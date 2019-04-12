#include "cq_lua_runtime.h"
#include "cq_lua_foundation.h"

void cq_lua_vm_load_libs() {
    
    cq_lua_load_lib_runtime();
    cq_lua_load_lib_foundation();
}
