#include "cqluaruntime.h"
#include "cqluaapi.h"

void cq_lua_load_lib_runtime() {
    const char *source = nullptr;
    #include "cqluaruntime_lua.h"
    cq_lua_do_string(source);
}
