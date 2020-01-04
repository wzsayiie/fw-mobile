#pragma once

#include "CLSDEF.hh"
#include "toolset.hh"

//clear the meta infomation before pick new meta.
void cls_picker_reset();

//set package name or class prefix of the generated code.
void set_java_pkg(const string &name);
void set_objc_fix(const string &name);
void set_w32_fix (const string &name);
void set_cpp_fix (const string &name);
void set_lua_fix (const string &name);

//append meta information:

struct param_desc {
    _type  type;
    string name;
};

struct func_desc {
    _type  retv;
    string name;
    
    vector<param_desc> params;
};

struct cls_desc {
    _type type;

    vector<func_desc> cls_fs;
    vector<func_desc> obj_fs;
};

void append_cls(_type type);
void append_cls_func(const string &name);
void append_obj_func(const string &name);
void append_param(_type type, const string &name);
void append_retv(_type type);

//get meta information:

string get_java_pkg();
string get_objc_fix();
string get_w32_fix ();
string get_cpp_fix ();
string get_lua_fix ();

vector<cls_desc> get_cls_list();
