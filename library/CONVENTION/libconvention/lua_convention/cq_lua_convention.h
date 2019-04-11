#pragma once

#include "cq_convention.h"

typedef struct lua_State lua_State;
typedef int32_t (*lua_CFunction)(lua_State *);

CQ_C_LINK void cq_lua_register_func(const char *name, lua_CFunction func);
CQ_C_LINK void cq_lua_do_string(const char *code);

CQ_C_LINK bool    cq_lua_check_bool  (lua_State *state, int32_t index);
CQ_C_LINK int8_t  cq_lua_check_int8  (lua_State *state, int32_t index);
CQ_C_LINK int16_t cq_lua_check_int16 (lua_State *state, int32_t index);
CQ_C_LINK int32_t cq_lua_check_int32 (lua_State *state, int32_t index);
CQ_C_LINK int64_t cq_lua_check_int64 (lua_State *state, int32_t index);
CQ_C_LINK float   cq_lua_check_float (lua_State *state, int32_t index);
CQ_C_LINK double  cq_lua_check_double(lua_State *state, int32_t index);
CQ_C_LINK PCSTR   cq_lua_check_string(lua_State *state, int32_t index);

CQ_C_LINK void cq_lua_push_bool  (lua_State *state, bool    value);
CQ_C_LINK void cq_lua_push_int8  (lua_State *state, int8_t  value);
CQ_C_LINK void cq_lua_push_int16 (lua_State *state, int16_t value);
CQ_C_LINK void cq_lua_push_int32 (lua_State *state, int32_t value);
CQ_C_LINK void cq_lua_push_int64 (lua_State *state, int64_t value);
CQ_C_LINK void cq_lua_push_float (lua_State *state, float   value);
CQ_C_LINK void cq_lua_push_double(lua_State *state, double  value);
CQ_C_LINK void cq_lua_push_string(lua_State *state, PCSTR   value);

CQ_C_LINK void cq_lua_load_lib_convention(void);

//host need set specified handlers ->

CQ_C_LINK void _cq_lua_set_register_func_h(void (*h)(const char *, lua_CFunction));
CQ_C_LINK void _cq_lua_set_do_string_h    (void (*h)(const char *));

CQ_C_LINK void _cq_lua_set_check_integer_h(int64_t (*h)(lua_State *, int32_t));
CQ_C_LINK void _cq_lua_set_check_double_h (double  (*h)(lua_State *, int32_t));
CQ_C_LINK void _cq_lua_set_check_string_h (PCSTR   (*h)(lua_State *, int32_t));

CQ_C_LINK void _cq_lua_set_push_integer_h(void (*h)(lua_State *, int64_t));
CQ_C_LINK void _cq_lua_set_push_double_h (void (*h)(lua_State *, double ));
CQ_C_LINK void _cq_lua_set_push_string_h (void (*h)(lua_State *, PCSTR  ));
