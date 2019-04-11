#include "cq_lua_convention.h"
#include "cqconvention.hh"

static void (*_register_func)(const char *name, int32_t (*func)(lua_State *)) = nullptr;
static void (*_do_string    )(const char *source                            ) = nullptr;

static int64_t     (*_check_integer)(lua_State *, int32_t) = nullptr;
static double      (*_check_double )(lua_State *, int32_t) = nullptr;
static const char *(*_check_string )(lua_State *, int32_t) = nullptr;

static void (*_push_integer)(lua_State *, int64_t     ) = nullptr;
static void (*_push_double )(lua_State *, double      ) = nullptr;
static void (*_push_string )(lua_State *, const char *) = nullptr;

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

static map<string, int32_t (*)(lua_State *)> *_func_store() {
    static map<string, int32_t (*)(lua_State *)> *object = nullptr;
    if (object == nullptr) {
        object = new map<string, int32_t (*)(lua_State *)>;
    }
    return object;
}

static vector<string> *_string_store() {
    static vector<string> *object = nullptr;
    if (object == nullptr) {
        object = new vector<string>;
    }
    return object;
}

void cq_lua_add_func(const char *name, int (*func)(lua_State *)) {
    if (name && func) {
        (*_func_store())[name] = func;
    }
}

void cq_lua_add_string(const char *code) {
    if (code) {
        _string_store()->push_back(code);
    }
}

void cq_lua_register_added_func() {
    if (_register_func) {
        auto store = _func_store();
        for (const auto &it : *store) {
            _register_func(it.first.c_str(), it.second);
        }
        store->clear();
    }
}

void cq_lua_do_added_string() {
    if (_do_string) {
        auto store = _string_store();
        for (const auto &it : *store) {
            _do_string(it.c_str());
        }
        store->clear();
    }
}

bool        cq_lua_check_bool  (lua_State *s, int32_t i) {return _check_integer ? (bool   )_check_integer(s, i) : 0;}
int8_t      cq_lua_check_int8  (lua_State *s, int32_t i) {return _check_integer ? (int8_t )_check_integer(s, i) : 0;}
int16_t     cq_lua_check_int16 (lua_State *s, int32_t i) {return _check_integer ? (int16_t)_check_integer(s, i) : 0;}
int32_t     cq_lua_check_int32 (lua_State *s, int32_t i) {return _check_integer ? (int32_t)_check_integer(s, i) : 0;}
int64_t     cq_lua_check_int64 (lua_State *s, int32_t i) {return _check_integer ?          _check_integer(s, i) : 0;}
float       cq_lua_check_float (lua_State *s, int32_t i) {return _check_double  ? (float  )_check_double (s, i) : 0;}
double      cq_lua_check_double(lua_State *s, int32_t i) {return _check_double  ?          _check_double (s, i) : 0;}
const char *cq_lua_check_string(lua_State *s, int32_t i) {return _check_string  ?          _check_string (s, i) : 0;}

void cq_lua_push_bool  (lua_State *s, bool        v) {if (_push_integer) _push_integer(s, v);}
void cq_lua_push_int8  (lua_State *s, int8_t      v) {if (_push_integer) _push_integer(s, v);}
void cq_lua_push_int16 (lua_State *s, int16_t     v) {if (_push_integer) _push_integer(s, v);}
void cq_lua_push_int32 (lua_State *s, int32_t     v) {if (_push_integer) _push_integer(s, v);}
void cq_lua_push_int64 (lua_State *s, int64_t     v) {if (_push_integer) _push_integer(s, v);}
void cq_lua_push_float (lua_State *s, float       v) {if (_push_double ) _push_double (s, v);}
void cq_lua_push_double(lua_State *s, double      v) {if (_push_double ) _push_double (s, v);}
void cq_lua_push_string(lua_State *s, const char *v) {if (_push_string ) _push_string (s, v);}

void _cq_lua_set_register_func_h(void (*h)(const char *n, int32_t (*f)(lua_State *))) {_register_func = h;}
void _cq_lua_set_do_string_h    (void (*h)(const char *c                           )) {_do_string     = h;}

void _cq_lua_set_check_integer_h(int64_t     (*h)(lua_State *, int32_t)) {_check_integer = h;}
void _cq_lua_set_check_double_h (double      (*h)(lua_State *, int32_t)) {_check_double  = h;}
void _cq_lua_set_check_string_h (const char *(*h)(lua_State *, int32_t)) {_check_string  = h;}

void _cq_lua_set_push_integer_h(void (*h)(lua_State *, int64_t     )) {_push_integer = h;}
void _cq_lua_set_push_double_h (void (*h)(lua_State *, double      )) {_push_double  = h;}
void _cq_lua_set_push_string_h (void (*h)(lua_State *, const char *)) {_push_string  = h;}

CQ_LUA_STRING(get_source)() {
    const char *source = nullptr;
    #include "cq_lua_convention.lua.h"
    return source;
}
