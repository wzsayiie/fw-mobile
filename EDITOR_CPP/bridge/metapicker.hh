#pragma once

#include "CLSDEF.hh"
#include "toolset.hh"

//clear the meta infomation.
void meta_reset();

//set location of generated files.
void set_java_source(const string &dir );
void set_java_native(const string &file);
void set_objc_header(const string &file);
void set_objc_source(const string &file);
void set_objc_prefix(const string &pref);
void set_w32_header (const string &file);
void set_w32_source (const string &file);
void set_w32_prefix (const string &pref);
void set_cpp_header (const string &file);
void set_cpp_source (const string &file);
void set_cpp_prefix (const string &pref);
void set_lua_cpp_h  (const string &file);
void set_lua_cpp_s  (const string &file);
void set_lua_script (const string &file);
void set_lua_prefix (const string &pref);
void set_lua_load_f (const string &name);

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

//get the meta information:

struct meta_info {
    string java_source;
    string java_native;

    string objc_header;
    string objc_source;
    string objc_prefix;

    string w32_header;
    string w32_source;
    string w32_prefix;

    string cpp_header;
    string cpp_source;
    string cpp_prefix;

    string lua_cpp_h;
    string lua_cpp_s;
    string lua_script;
    string lua_prefix;
    string lua_load_f;
    
    vector<cls_desc> cls_list;
};

meta_info get_meta();
