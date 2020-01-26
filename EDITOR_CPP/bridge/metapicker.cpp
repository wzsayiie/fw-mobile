#include "metapicker.hh"

static meta_info _meta;
static bool _cur_cls_func = false;

void reset_meta() {
    _meta = meta_info();
}

void set_lib_type(lib_type type) {
    _meta.type = type;
}

void set_java_source(const string &dir ) {_meta.java_source = dir ;}
void set_java_native(const string &file) {_meta.java_native = file;}
void set_objc_header(const string &file) {_meta.objc_header = file;}
void set_objc_source(const string &file) {_meta.objc_source = file;}
void set_objc_prefix(const string &pref) {_meta.objc_prefix = pref;}
void set_w32_header (const string &file) {_meta.w32_header  = file;}
void set_w32_source (const string &file) {_meta.w32_source  = file;}
void set_w32_prefix (const string &pref) {_meta.w32_prefix  = pref;}
void set_cpp_header (const string &file) {_meta.cpp_header  = file;}
void set_cpp_source (const string &file) {_meta.cpp_source  = file;}
void set_cpp_prefix (const string &pref) {_meta.cpp_prefix  = pref;}
void set_lua_cpp_h  (const string &file) {_meta.lua_cpp_h   = file;}
void set_lua_cpp_s  (const string &file) {_meta.lua_cpp_s   = file;}
void set_lua_script (const string &file) {_meta.lua_script  = file;}
void set_lua_prefix (const string &pref) {_meta.lua_prefix  = pref;}
void set_lua_load_f (const string &name) {_meta.lua_load_f  = name;}

void append_cls(_type type) {
    cls_desc cls; {
        cls.type = type;
    }
    _meta.cls_list.push_back(cls);
}

static
void append_func(vector<func_desc> *fs, const string &name) {
    func_desc func; {
        func.name = name;
    }
    fs->push_back(func);
}

void append_cls_func(const string &name) {
    if (_meta.cls_list.empty()) {
        return;
    }
     
    cls_desc &cls = _meta.cls_list.back();
    append_func(&cls.cls_fs, name);
    
    _cur_cls_func = true;
}

void append_obj_func(const string &name) {
    if (_meta.cls_list.empty()) {
        return;
    }
     
    cls_desc &cls = _meta.cls_list.back();
    append_func(&cls.obj_fs, name);
    
    _cur_cls_func = false;
}

static
void append_param(vector<func_desc> *fs, _type type, const string &name) {
    if (fs->empty()) {
        return;
    }
    
    func_desc &func = fs->back();
    
    param_desc param; {
        param.type = type;
        param.name = name;
    }
    func.params.push_back(param);
}

void append_param(_type type, const string &name) {
    if (_meta.cls_list.empty()) {
        return;
    }
    
    cls_desc &cls = _meta.cls_list.back();
    if (_cur_cls_func) {
        append_param(&cls.cls_fs, type, name);
    } else {
        append_param(&cls.obj_fs, type, name);
    }
}

static
void append_retv(vector<func_desc> *fs, _type type) {
    if (fs->empty()) {
        return;
    }
    
    func_desc &func = fs->back();
    func.retv = type;
}

void append_retv(_type type) {
    if (_meta.cls_list.empty()) {
        return;
    }
    
    cls_desc &cls = _meta.cls_list.back();
    if (_cur_cls_func) {
        append_retv(&cls.cls_fs, type);
    } else {
        append_retv(&cls.obj_fs, type);
    }
}

meta_info get_meta() {
    return _meta;
}
