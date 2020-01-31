#include "metapicker.hh"

static meta_info _meta;
static func_desc *_on_func = nullptr;

void reset_meta() {
    _meta = meta_info();
}

void set_lib_type(target_lib_type type) {
    _meta.lib_type = type;
}

void set_java_source(const string &a) {_meta.java_source = a;}
void set_java_native(const string &a) {_meta.java_native = a;}
void set_java_pkg   (const string &a) {_meta.java_pkg    = a;}
void set_objc_header(const string &a) {_meta.objc_header = a;}
void set_objc_source(const string &a) {_meta.objc_source = a;}
void set_objc_prefix(const string &a) {_meta.objc_prefix = a;}
void set_w32_header (const string &a) {_meta.w32_header  = a;}
void set_w32_source (const string &a) {_meta.w32_source  = a;}
void set_w32_prefix (const string &a) {_meta.w32_prefix  = a;}
void set_cpp_header (const string &a) {_meta.cpp_header  = a;}
void set_cpp_source (const string &a) {_meta.cpp_source  = a;}
void set_cpp_prefix (const string &a) {_meta.cpp_prefix  = a;}
void set_lua_cpp_h  (const string &a) {_meta.lua_cpp_h   = a;}
void set_lua_cpp_s  (const string &a) {_meta.lua_cpp_s   = a;}
void set_lua_script (const string &a) {_meta.lua_script  = a;}
void set_lua_prefix (const string &a) {_meta.lua_prefix  = a;}
void set_lua_load_f (const string &a) {_meta.lua_load_f  = a;}

void append_cls(_type type) {
    cls_desc cls; {
        cls.type = type;
    }
    _meta.cls_list.push_back(cls);
}

static void append_func(bool is_cls_func, const string &name) {
    if (_meta.cls_list.empty()) {
        return;
    }
    
    func_desc func; {
        func.name = name;
    }
    
    cls_desc &cls = _meta.cls_list.back();
    if (is_cls_func) {
        cls.cls_fs.push_back(func);
        _on_func = &cls.cls_fs.back();
    } else {
        cls.obj_fs.push_back(func);
        _on_func = &cls.obj_fs.back();
    }
}

void append_cls_func(const string &n) {append_func(true , n);}
void append_obj_func(const string &n) {append_func(false, n);}

void append_param(_type type, const string &name) {
    if (_on_func == nullptr) {
        return;
    }
    
    param_desc param; {
        param.type = type;
        param.name = name;
    }
    _on_func->params.push_back(param);
}

void append_retv(_type type) {
    if (_on_func == nullptr) {
        return;
    }
    
    _on_func->retv = type;
}

meta_info get_meta() {
    return _meta;
}
