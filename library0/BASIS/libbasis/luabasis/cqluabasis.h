#pragma once

#include "cqcbasis.h"

struct lua_State;
typedef int32_t (*lua_CFunction)(struct lua_State *);

CQ_C_LINK void cq_lua_register_tab (const char *tab, const char *base);
CQ_C_LINK void cq_lua_register_func(const char *tab, const char *func, lua_CFunction ptr);

CQ_C_LINK void cq_lua_do_string(const char *code);

CQ_C_LINK bool    cq_lua_check_bool  (struct lua_State *state, int32_t index);
CQ_C_LINK int8_t  cq_lua_check_int8  (struct lua_State *state, int32_t index);
CQ_C_LINK int16_t cq_lua_check_int16 (struct lua_State *state, int32_t index);
CQ_C_LINK int32_t cq_lua_check_int32 (struct lua_State *state, int32_t index);
CQ_C_LINK int64_t cq_lua_check_int64 (struct lua_State *state, int32_t index);
CQ_C_LINK float   cq_lua_check_float (struct lua_State *state, int32_t index);
CQ_C_LINK double  cq_lua_check_double(struct lua_State *state, int32_t index);

CQ_C_LINK const char *cq_lua_check_string(struct lua_State *state, int32_t index);

CQ_C_LINK int32_t cq_lua_return_void  (struct lua_State *state);
CQ_C_LINK int32_t cq_lua_return_bool  (struct lua_State *state, bool    value);
CQ_C_LINK int32_t cq_lua_return_int8  (struct lua_State *state, int8_t  value);
CQ_C_LINK int32_t cq_lua_return_int16 (struct lua_State *state, int16_t value);
CQ_C_LINK int32_t cq_lua_return_int32 (struct lua_State *state, int32_t value);
CQ_C_LINK int32_t cq_lua_return_int64 (struct lua_State *state, int64_t value);
CQ_C_LINK int32_t cq_lua_return_float (struct lua_State *state, float   value);
CQ_C_LINK int32_t cq_lua_return_double(struct lua_State *state, double  value);

CQ_C_LINK int32_t cq_lua_return_string(struct lua_State *state, const char *value);

//host need set these handlers ->

struct _cq_lua_handlers {
    
    void (*register_tab )(const char *tab, const char *base);
    void (*register_func)(const char *tab, const char *func, lua_CFunction ptr);
    
    void (*do_string)(const char *code);
    
    int64_t (*check_integer)(struct lua_State *state, int32_t index);
    double  (*check_double )(struct lua_State *state, int32_t index);
    
    const char *(*check_string)(struct lua_State *state, int32_t index);
    
    void (*push_bool   )(struct lua_State *state, bool    value);
    void (*push_integer)(struct lua_State *state, int64_t value);
    void (*push_double )(struct lua_State *state, double  value);
    
    void (*push_string)(struct lua_State *state, const char *value);
};

CQ_C_LINK void _cq_lua_set_handlers(struct _cq_lua_handlers *handlers);
