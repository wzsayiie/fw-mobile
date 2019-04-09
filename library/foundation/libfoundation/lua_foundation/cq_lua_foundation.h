#pragma once

#include "cq_convention.h"

CQ_C_LINK void cq_lua_foundation_open(void *lua_state, void (*execute)(const char *));
