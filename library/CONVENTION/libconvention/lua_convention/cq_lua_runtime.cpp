#include "cq_lua_runtime.h"
#include "cq_lua_api.h"

void cq_lua_load_lib_runtime() {
    const char *source = nullptr;
    #include "cq_lua_runtime.lua.h"
    cq_lua_do_string(source);
}
