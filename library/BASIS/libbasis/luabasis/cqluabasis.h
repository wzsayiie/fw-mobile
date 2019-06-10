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

CQ_C_LINK int32_t cq_lua_return_void  (lua_State *state);
CQ_C_LINK int32_t cq_lua_return_bool  (lua_State *state, bool    value);
CQ_C_LINK int32_t cq_lua_return_int8  (lua_State *state, int8_t  value);
CQ_C_LINK int32_t cq_lua_return_int16 (lua_State *state, int16_t value);
CQ_C_LINK int32_t cq_lua_return_int32 (lua_State *state, int32_t value);
CQ_C_LINK int32_t cq_lua_return_int64 (lua_State *state, int64_t value);
CQ_C_LINK int32_t cq_lua_return_float (lua_State *state, float   value);
CQ_C_LINK int32_t cq_lua_return_double(lua_State *state, double  value);
CQ_C_LINK int32_t cq_lua_return_string(lua_State *state, PCSTR   value);

//host need set these handlers ->

typedef struct _cq_lua_handlers {
    
    void (*register_func)(const char *name, lua_CFunction);
    void (*do_string    )(const char *code);
    
    int64_t (*check_integer)(lua_State *state, int32_t index);
    double  (*check_double )(lua_State *state, int32_t index);
    PCSTR   (*check_string )(lua_State *state, int32_t index);
    
    void (*push_bool   )(lua_State *state, bool    value);
    void (*push_integer)(lua_State *state, int64_t value);
    void (*push_double )(lua_State *state, double  value);
    void (*push_string )(lua_State *state, PCSTR   value);
    
} _cq_lua_handlers;

extern const _cq_lua_handlers _cq_lua_handlers_zero;

CQ_C_LINK void _cq_lua_set_handlers(_cq_lua_handlers *handlers);
