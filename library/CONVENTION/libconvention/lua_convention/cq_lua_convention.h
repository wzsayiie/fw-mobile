#pragma once

#include "cq_convention.h"

typedef struct lua_State lua_State;

CQ_C_LINK void cq_lua_register_func(const char *name, int32_t (*func)(lua_State *));
CQ_C_LINK void cq_lua_do_string(const char *code);

CQ_C_LINK void cq_lua_add_func(const char *name, int32_t (*func)(lua_State *));
CQ_C_LINK void cq_lua_add_string(const char *code);

CQ_C_LINK void cq_lua_register_added_func(void);
CQ_C_LINK void cq_lua_do_added_string(void);

#ifdef __cplusplus

struct _cq_lua_func_adder {
    _cq_lua_func_adder(const char *name, int32_t (*func)(lua_State *)) {
        cq_lua_add_func(name, func);
    }
};

struct _cq_lua_string_adder {
    _cq_lua_string_adder(const char *code) {
        cq_lua_add_string(code);
    }
};

#define CQ_LUA_FUNC(name)\
/**/    static int lua_f_##name(lua_State *state);\
/**/    static _cq_lua_func_adder lua_f_adder_##name(""#name, lua_f_##name);\
/**/    static int lua_f_##name

#define CQ_LUA_STRING(name)\
/**/    static const char *lua_s_##name();\
/**/    static _cq_lua_string_adder lua_s_adder_##name(lua_s_##name());\
/**/    static const char *lua_s_##name

#endif

CQ_C_LINK bool        cq_lua_check_bool  (lua_State *state, int32_t index);
CQ_C_LINK int8_t      cq_lua_check_int8  (lua_State *state, int32_t index);
CQ_C_LINK int16_t     cq_lua_check_int16 (lua_State *state, int32_t index);
CQ_C_LINK int32_t     cq_lua_check_int32 (lua_State *state, int32_t index);
CQ_C_LINK int64_t     cq_lua_check_int64 (lua_State *state, int32_t index);
CQ_C_LINK float       cq_lua_check_float (lua_State *state, int32_t index);
CQ_C_LINK double      cq_lua_check_double(lua_State *state, int32_t index);
CQ_C_LINK const char *cq_lua_check_string(lua_State *state, int32_t index);

CQ_C_LINK void cq_lua_push_bool  (lua_State *state, bool        value);
CQ_C_LINK void cq_lua_push_int8  (lua_State *state, int8_t      value);
CQ_C_LINK void cq_lua_push_int16 (lua_State *state, int16_t     value);
CQ_C_LINK void cq_lua_push_int32 (lua_State *state, int32_t     value);
CQ_C_LINK void cq_lua_push_int64 (lua_State *state, int64_t     value);
CQ_C_LINK void cq_lua_push_float (lua_State *state, float       value);
CQ_C_LINK void cq_lua_push_double(lua_State *state, double      value);
CQ_C_LINK void cq_lua_push_string(lua_State *state, const char *value);

//host need set specified handlers ->

CQ_C_LINK void _cq_lua_set_register_func_h(void (*h)(const char *name, int (*func)(lua_State *)));
CQ_C_LINK void _cq_lua_set_do_string_h    (void (*h)(const char *code                          ));

CQ_C_LINK void _cq_lua_set_check_integer_h(int64_t     (*h)(lua_State *, int32_t));
CQ_C_LINK void _cq_lua_set_check_double_h (double      (*h)(lua_State *, int32_t));
CQ_C_LINK void _cq_lua_set_check_string_h (const char *(*h)(lua_State *, int32_t));

CQ_C_LINK void _cq_lua_set_push_integer_h(void (*h)(lua_State *, int64_t     ));
CQ_C_LINK void _cq_lua_set_push_double_h (void (*h)(lua_State *, double      ));
CQ_C_LINK void _cq_lua_set_push_string_h (void (*h)(lua_State *, const char *));
