#pragma once

#include "cqcbasis.h"

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

CQ_C_LINK int32_t cq_lua_push_void  (lua_State *state);
CQ_C_LINK int32_t cq_lua_push_bool  (lua_State *state, bool    value);
CQ_C_LINK int32_t cq_lua_push_int8  (lua_State *state, int8_t  value);
CQ_C_LINK int32_t cq_lua_push_int16 (lua_State *state, int16_t value);
CQ_C_LINK int32_t cq_lua_push_int32 (lua_State *state, int32_t value);
CQ_C_LINK int32_t cq_lua_push_int64 (lua_State *state, int64_t value);
CQ_C_LINK int32_t cq_lua_push_float (lua_State *state, float   value);
CQ_C_LINK int32_t cq_lua_push_double(lua_State *state, double  value);
CQ_C_LINK int32_t cq_lua_push_string(lua_State *state, PCSTR   value);

//host need set these handlers ->

CQ_C_LINK void _cq_lua_set_register_func_handler(void (*h)(const char *, lua_CFunction));
CQ_C_LINK void _cq_lua_set_do_string_handler    (void (*h)(const char *));

CQ_C_LINK void _cq_lua_set_check_integer_handler(int64_t (*h)(lua_State *, int32_t));
CQ_C_LINK void _cq_lua_set_check_double_handler (double  (*h)(lua_State *, int32_t));
CQ_C_LINK void _cq_lua_set_check_string_handler (PCSTR   (*h)(lua_State *, int32_t));

CQ_C_LINK void _cq_lua_set_push_bool_handler   (void (*h)(lua_State *, bool   ));
CQ_C_LINK void _cq_lua_set_push_integer_handler(void (*h)(lua_State *, int64_t));
CQ_C_LINK void _cq_lua_set_push_double_handler (void (*h)(lua_State *, double ));
CQ_C_LINK void _cq_lua_set_push_string_handler (void (*h)(lua_State *, PCSTR  ));
