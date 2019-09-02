#pragma once

#include "cqluabasis.h"

CQ_C_LINK void cq_lua_open_vm(const char *directory);
CQ_C_LINK void cq_lua_close_vm(void);
