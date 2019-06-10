#include "cqluabasis.h"
#include "cqcppbasis.hh"

extern const _cq_lua_handlers _cq_lua_handlers_zero = {nullptr};
static _cq_lua_handlers _h = {nullptr};

template<class F, class... A> auto call(F func, A... args) -> decltype(func(args...)) {
    if (func != nullptr) {
        return func(args...);
    } else {
        return decltype(func(args...))();
    }
}

void cq_lua_register_func(const char *name, int (*func)(lua_State *)) {
    return call(_h.register_func, name, func);
}

void cq_lua_do_string(const char *code) {
    return call(_h.do_string, code);
}

bool    cq_lua_check_bool  (lua_State *s, int32_t i) {return (bool   )call(_h.check_integer, s, i);}
int8_t  cq_lua_check_int8  (lua_State *s, int32_t i) {return (int8_t )call(_h.check_integer, s, i);}
int16_t cq_lua_check_int16 (lua_State *s, int32_t i) {return (int16_t)call(_h.check_integer, s, i);}
int32_t cq_lua_check_int32 (lua_State *s, int32_t i) {return (int32_t)call(_h.check_integer, s, i);}
int64_t cq_lua_check_int64 (lua_State *s, int32_t i) {return (int64_t)call(_h.check_integer, s, i);}
float   cq_lua_check_float (lua_State *s, int32_t i) {return (float  )call(_h.check_double , s, i);}
double  cq_lua_check_double(lua_State *s, int32_t i) {return (double )call(_h.check_double , s, i);}
PCSTR   cq_lua_check_string(lua_State *s, int32_t i) {return (PCSTR  )call(_h.check_string , s, i);}

int32_t cq_lua_return_void  (lua_State *s           ) {                             return 0;}
int32_t cq_lua_return_bool  (lua_State *s, bool    v) {call(_h.push_bool   , s, v); return 1;}
int32_t cq_lua_return_int8  (lua_State *s, int8_t  v) {call(_h.push_integer, s, v); return 1;}
int32_t cq_lua_return_int16 (lua_State *s, int16_t v) {call(_h.push_integer, s, v); return 1;}
int32_t cq_lua_return_int32 (lua_State *s, int32_t v) {call(_h.push_integer, s, v); return 1;}
int32_t cq_lua_return_int64 (lua_State *s, int64_t v) {call(_h.push_integer, s, v); return 1;}
int32_t cq_lua_return_float (lua_State *s, float   v) {call(_h.push_double , s, v); return 1;}
int32_t cq_lua_return_double(lua_State *s, double  v) {call(_h.push_double , s, v); return 1;}
int32_t cq_lua_return_string(lua_State *s, PCSTR   v) {call(_h.push_string , s, v); return 1;}

void _cq_lua_set_handlers(_cq_lua_handlers *handlers) {
    if (handlers != nullptr) {
        _h = *handlers;
    } else {
        _h = _cq_lua_handlers_zero;
    }
}
