#include "CLSDEFLANG.hh"
#include "metapicker.hh"

void def_local_lib() {set_lib_type(local_lib);}
void def_cpp_lib  () {set_lib_type(cpp_lib  );}

void java_source(const char *a) {set_java_source(a);}
void java_native(const char *a) {set_java_native(a);}
void objc_header(const char *a) {set_objc_header(a);}
void objc_source(const char *a) {set_objc_source(a);}
void w32_header (const char *a) {set_w32_header (a);}
void w32_source (const char *a) {set_w32_source (a);}
void cpp_header (const char *a) {set_cpp_header (a);}
void cpp_source (const char *a) {set_cpp_source (a);}
void lua_cpp_h  (const char *a) {set_lua_cpp_h  (a);}
void lua_cpp_s  (const char *a) {set_lua_cpp_s  (a);}
void lua_script (const char *a) {set_lua_script (a);}

void java_pkg   (const char *a) {set_java_pkg   (a);}
void objc_prefix(const char *a) {set_objc_prefix(a);}
void w32_prefix (const char *a) {set_w32_prefix (a);}
void cpp_prefix (const char *a) {set_cpp_prefix (a);}
void lua_prefix (const char *a) {set_lua_prefix (a);}

void lua_load_f (const char *a) {set_lua_load_f (a);}

_def::_def(const char *name) {
    this->iden = _type_id_cls;
    this->name = name;
    
    append_cls(*this);
}

static bool _statik_flag = false;

void _statik() {
    _statik_flag = true;
}

_func_back _func_back::operator()()
{
    return *this;
}
_func_back _func_back::operator()(
    const char *name1, _type type1)
{
    append_param(type1, name1);
    
    return *this;
}
_func_back _func_back::operator()(
    const char *name1, _type type1,
    const char *name2, _type type2)
{
    append_param(type1, name1);
    append_param(type2, name2);
    
    return *this;
}
_func_back _func_back::operator()(
    const char *name1, _type type1,
    const char *name2, _type type2,
    const char *name3, _type type3)
{
    append_param(type1, name1);
    append_param(type2, name2);
    append_param(type3, name3);

    return *this;
}
_func_back _func_back::operator()(
    const char *name1, _type type1,
    const char *name2, _type type2,
    const char *name3, _type type3,
    const char *name4, _type type4)
{
    append_param(type1, name1);
    append_param(type2, name2);
    append_param(type3, name3);
    append_param(type4, name4);
    
    return *this;
}

void _func_back::operator>>(_type type) {
    append_retv(type);
}

_func_back func(const char *name) {
    if (_statik_flag) {
        append_cls_func(name);
        _statik_flag = false;
    } else {
        append_obj_func(name);
    }
    return _func_back();
}
