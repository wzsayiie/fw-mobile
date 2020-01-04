#include "CLSDEF.hh"
#include "clspicker.hh"

void java_pkg(const char *name) {set_java_pkg(name);}
void objc_fix(const char *name) {set_objc_fix(name);}
void w32_fix (const char *name) {set_w32_fix (name);}
void cpp_fix (const char *name) {set_cpp_fix (name);}
void lua_fix (const char *name) {set_lua_fix (name);}

static bool _loc_flag = false;
static bool _cpp_flag = false;

void _loc() {_loc_flag = true;}
void _cpp() {_cpp_flag = true;}

_def::_def(const char *name) {
    /**/ if (_loc_flag) {this->iden = _type_id_loc_cls; _loc_flag = false;}
    else if (_cpp_flag) {this->iden = _type_id_cpp_cls; _cpp_flag = false;}
    else /*..........*/ {this->iden = _type_id_cls    ;}
    
    this->name = name;
    
    append_cls(*this);
}

static bool _statical_flag = false;

void _statical() {
    _statical_flag = true;
}

_func_back _func_back::operator()()
{
    return *this;
}
_func_back _func_back::operator()(
    const char * name1, _type type1)
{
    append_param(type1, name1);
    
    return *this;
}
_func_back _func_back::operator()(
    const char * name1, _type type1,
    const char * name2, _type type2)
{
    append_param(type1, name1);
    append_param(type2, name2);
    
    return *this;
}
_func_back _func_back::operator()(
    const char * name1, _type type1,
    const char * name2, _type type2,
    const char * name3, _type type3)
{
    append_param(type1, name1);
    append_param(type2, name2);
    append_param(type3, name3);

    return *this;
}
_func_back _func_back::operator()(
    const char * name1, _type type1,
    const char * name2, _type type2,
    const char * name3, _type type3,
    const char * name4, _type type4)
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
    if (_statical_flag) {
        append_cls_func(name);
        _statical_flag = false;
    } else {
        append_obj_func(name);
    }
    return _func_back();
}
