#include "cqluafoundation.h"
#include "cqluasubsystem.h"

void cq_lua_vm_load_libs() {
    
    cq_lua_load_lib_runtime();
    cq_lua_load_lib_foundation();
    cq_lua_load_lib_subsystem();
}
