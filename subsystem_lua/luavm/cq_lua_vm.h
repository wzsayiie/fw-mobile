#pragma once

#include "cq_convention.h"

typedef struct lua_State lua_State;

CQ_C_LINK lua_State *cq_lua_vm_open(const char *directory_path);
CQ_C_LINK void cq_lua_vm_close(void);

CQ_C_LINK void cq_lua_vm_do_string(const char *source);
