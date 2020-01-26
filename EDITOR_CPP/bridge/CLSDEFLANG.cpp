#include "CLSDEFLANG.hh"
#include "metapicker.hh"

void def_local_lib() {set_lib_type(local_lib);}
void def_cpp_lib  () {set_lib_type(cpp_lib  );}

void java_source(const char *dir ) {set_java_source(dir );}
void java_native(const char *file) {set_java_native(file);}
void objc_header(const char *file) {set_objc_header(file);}
void objc_source(const char *file) {set_objc_source(file);}
void w32_header (const char *file) {set_w32_header (file);}
void w32_source (const char *file) {set_w32_source (file);}
void cpp_header (const char *file) {set_cpp_header (file);}
void cpp_source (const char *file) {set_cpp_source (file);}
void lua_cpp_h  (const char *file) {set_lua_cpp_h  (file);}
void lua_cpp_s  (const char *file) {set_lua_cpp_s  (file);}
void lua_script (const char *file) {set_lua_script (file);}

void objc_prefix(const char *pref) {set_objc_prefix(pref);}
void w32_prefix (const char *pref) {set_w32_prefix (pref);}
void cpp_prefix (const char *pref) {set_cpp_prefix (pref);}
void lua_prefix (const char *pref) {set_lua_prefix (pref);}
void lua_load_f (const char *name) {set_lua_load_f (name);}

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
