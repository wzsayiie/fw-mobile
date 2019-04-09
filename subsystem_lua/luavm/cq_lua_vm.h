#pragma once

#include "cq_convention.h"

CQ_C_LINK void cq_lua_vm_open(const char *directory_path);
CQ_C_LINK void cq_lua_vm_close(void);

CQ_C_LINK void cq_lua_vm_do_string(const char *source);
