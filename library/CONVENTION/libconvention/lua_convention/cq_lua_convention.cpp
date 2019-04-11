#include "cq_lua_convention.h"
#include "cqconvention.hh"

static void (*_register_func)(const char *, lua_CFunction) = nullptr;
static void (*_do_string    )(const char *) = nullptr;

static int64_t (*_check_integer)(lua_State *, int32_t) = nullptr;
static double  (*_check_double )(lua_State *, int32_t) = nullptr;
static PCSTR   (*_check_string )(lua_State *, int32_t) = nullptr;

static void (*_push_integer)(lua_State *, int64_t) = nullptr;
static void (*_push_double )(lua_State *, double ) = nullptr;
static void (*_push_string )(lua_State *, PCSTR  ) = nullptr;

void cq_lua_register_func(const char *name, int (*func)(lua_State *)) {
    if (_register_func) {
        _register_func(name, func);
    }
}

void cq_lua_do_string(const char *code) {
    if (_do_string) {
        _do_string(code);
    }
}

void cq_lua_load_lib_convention() {
    const char *source = nullptr;
    #include "cq_lua_convention.lua.h"
    cq_lua_do_string(source);
}

bool    cq_lua_check_bool  (lua_State *s, int32_t i) {return _check_integer ? (bool   )_check_integer(s, i) : 0;}
int8_t  cq_lua_check_int8  (lua_State *s, int32_t i) {return _check_integer ? (int8_t )_check_integer(s, i) : 0;}
int16_t cq_lua_check_int16 (lua_State *s, int32_t i) {return _check_integer ? (int16_t)_check_integer(s, i) : 0;}
int32_t cq_lua_check_int32 (lua_State *s, int32_t i) {return _check_integer ? (int32_t)_check_integer(s, i) : 0;}
int64_t cq_lua_check_int64 (lua_State *s, int32_t i) {return _check_integer ? (int64_t)_check_integer(s, i) : 0;}
float   cq_lua_check_float (lua_State *s, int32_t i) {return _check_double  ? (float  )_check_double (s, i) : 0;}
double  cq_lua_check_double(lua_State *s, int32_t i) {return _check_double  ? (double )_check_double (s, i) : 0;}
PCSTR   cq_lua_check_string(lua_State *s, int32_t i) {return _check_string  ? (PCSTR  )_check_string (s, i) : 0;}

void cq_lua_push_bool  (lua_State *s, bool    v) {if (_push_integer) _push_integer(s, v);}
void cq_lua_push_int8  (lua_State *s, int8_t  v) {if (_push_integer) _push_integer(s, v);}
void cq_lua_push_int16 (lua_State *s, int16_t v) {if (_push_integer) _push_integer(s, v);}
void cq_lua_push_int32 (lua_State *s, int32_t v) {if (_push_integer) _push_integer(s, v);}
void cq_lua_push_int64 (lua_State *s, int64_t v) {if (_push_integer) _push_integer(s, v);}
void cq_lua_push_float (lua_State *s, float   v) {if (_push_double ) _push_double (s, v);}
void cq_lua_push_double(lua_State *s, double  v) {if (_push_double ) _push_double (s, v);}
void cq_lua_push_string(lua_State *s, PCSTR   v) {if (_push_string ) _push_string (s, v);}

void _cq_lua_set_register_func_h(void (*h)(const char *, lua_CFunction)) {_register_func = h;}
void _cq_lua_set_do_string_h    (void (*h)(const char *               )) {_do_string     = h;}

void _cq_lua_set_check_integer_h(int64_t (*h)(lua_State *, int32_t)) {_check_integer = h;}
void _cq_lua_set_check_double_h (double  (*h)(lua_State *, int32_t)) {_check_double  = h;}
void _cq_lua_set_check_string_h (PCSTR   (*h)(lua_State *, int32_t)) {_check_string  = h;}

void _cq_lua_set_push_integer_h(void (*h)(lua_State *, int64_t)) {_push_integer = h;}
void _cq_lua_set_push_double_h (void (*h)(lua_State *, double )) {_push_double  = h;}
void _cq_lua_set_push_string_h (void (*h)(lua_State *, PCSTR  )) {_push_string  = h;}
