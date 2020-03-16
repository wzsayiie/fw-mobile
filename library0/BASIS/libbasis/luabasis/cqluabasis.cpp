#include "cqluabasis.h"
#include "cqcppbasis.hh"

static _cq_lua_handlers _h = {nullptr};

template<class F, class... A> auto call(F func, A... args) -> decltype(func(args...)) {
    if (func != nullptr) {
        return func(args...);
    } else {
        return decltype(func(args...))();
    }
}

void cq_lua_register_tab (const char *a, const char *b                 ) {return call(_h.register_tab , a, b   );}
void cq_lua_register_func(const char *a, const char *b, lua_CFunction c) {return call(_h.register_func, a, b, c);}
void cq_lua_do_string    (const char *a                                ) {return call(_h.do_string    , a      );}

bool        cq_lua_check_bool  (lua_State *s, int32_t i) {return (bool   )call(_h.check_integer , s, i);}
int8_t      cq_lua_check_int8  (lua_State *s, int32_t i) {return (int8_t )call(_h.check_integer , s, i);}
int16_t     cq_lua_check_int16 (lua_State *s, int32_t i) {return (int16_t)call(_h.check_integer , s, i);}
int32_t     cq_lua_check_int32 (lua_State *s, int32_t i) {return (int32_t)call(_h.check_integer , s, i);}
int64_t     cq_lua_check_int64 (lua_State *s, int32_t i) {return          call(_h.check_integer , s, i);}
float       cq_lua_check_float (lua_State *s, int32_t i) {return (float  )call(_h.check_double  , s, i);}
double      cq_lua_check_double(lua_State *s, int32_t i) {return          call(_h.check_double  , s, i);}
const char *cq_lua_check_string(lua_State *s, int32_t i) {return          call(_h.check_string  , s, i);}
cq_obj     *cq_lua_check_object(lua_State *s, int32_t i) {return          call(_h.check_object  , s, i);}

void cq_lua_check_i64_list(lua_State *s, int32_t i, cq_i64_list_out p) {call(_h.check_i64_list, s, i, p);}
void cq_lua_check_str_list(lua_State *s, int32_t i, cq_str_list_out p) {call(_h.check_str_list, s, i, p);}
void cq_lua_check_ss_map  (lua_State *s, int32_t i, cq_ss_map_out   p) {call(_h.check_ss_map  , s, i, p);}

int32_t cq_lua_return_void  (lua_State *s               ) {                             return 0;}
int32_t cq_lua_return_bool  (lua_State *s, bool        v) {call(_h.push_bool   , s, v); return 1;}
int32_t cq_lua_return_int8  (lua_State *s, int8_t      v) {call(_h.push_integer, s, v); return 1;}
int32_t cq_lua_return_int16 (lua_State *s, int16_t     v) {call(_h.push_integer, s, v); return 1;}
int32_t cq_lua_return_int32 (lua_State *s, int32_t     v) {call(_h.push_integer, s, v); return 1;}
int32_t cq_lua_return_int64 (lua_State *s, int64_t     v) {call(_h.push_integer, s, v); return 1;}
int32_t cq_lua_return_float (lua_State *s, float       v) {call(_h.push_double , s, v); return 1;}
int32_t cq_lua_return_double(lua_State *s, double      v) {call(_h.push_double , s, v); return 1;}
int32_t cq_lua_return_string(lua_State *s, const char *v) {call(_h.push_string , s, v); return 1;}
int32_t cq_lua_return_object(lua_State *s, cq_obj     *v) {call(_h.push_object , s, v); return 1;}

int32_t cq_lua_return_i64_list(lua_State *s, cq_i64_list_in i) {call(_h.push_i64_list, s, i); return 1;}
int32_t cq_lua_return_str_list(lua_State *s, cq_str_list_in i) {call(_h.push_str_list, s, i); return 1;}
int32_t cq_lua_return_ss_map  (lua_State *s, cq_ss_map_in   i) {call(_h.push_ss_map  , s, i); return 1;}

void _cq_lua_set_handlers(_cq_lua_handlers *handlers) {
    if (handlers != nullptr) {
        _h = *handlers;
    } else {
        memset(&_h, 0, sizeof(_h));
    }
}
