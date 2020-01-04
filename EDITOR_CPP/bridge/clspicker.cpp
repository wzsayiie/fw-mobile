#include "clspicker.hh"

static string _java_pkg;
static string _objc_fix;
static string _w32_fix ;
static string _cpp_fix ;
static string _lua_fix ;

static vector<cls_desc> _cls_list;
static bool _cur_cls_func = false;

void cls_picker_reset() {
    
    _java_pkg.clear();
    _objc_fix.clear();
    _w32_fix .clear();
    _cpp_fix .clear();
    _lua_fix .clear();
    
    _cls_list.clear();
}

void set_java_pkg(const string &name) {_java_pkg = name;}
void set_objc_fix(const string &name) {_objc_fix = name;}
void set_w32_fix (const string &name) {_w32_fix  = name;}
void set_cpp_fix (const string &name) {_cpp_fix  = name;}
void set_lua_fix (const string &name) {_lua_fix  = name;}

void append_cls(_type type) {
    cls_desc cls; {
        cls.type = type;
    }
    _cls_list.push_back(cls);
}

static
void append_func(vector<func_desc> *fs, const string &name) {
    func_desc func; {
        func.name = name;
    }
    fs->push_back(func);
}

void append_cls_func(const string &name) {
    if (_cls_list.empty()) {
        return;
    }
     
    cls_desc &cls = _cls_list.back();
    append_func(&cls.cls_fs, name);
    
    _cur_cls_func = true;
}

void append_obj_func(const string &name) {
    if (_cls_list.empty()) {
        return;
    }
     
    cls_desc &cls = _cls_list.back();
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
    if (_cls_list.empty()) {
        return;
    }
    
    cls_desc &cls = _cls_list.back();
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
    if (_cls_list.empty()) {
        return;
    }
    
    cls_desc &cls = _cls_list.back();
    if (_cur_cls_func) {
        append_retv(&cls.cls_fs, type);
    } else {
        append_retv(&cls.obj_fs, type);
    }
}

string get_java_pkg() {return _java_pkg;}
string get_objc_fix() {return _objc_fix;}
string get_w32_fix () {return _w32_fix ;}
string get_cpp_fix () {return _cpp_fix ;}
string get_lua_fix () {return _lua_fix ;}

vector<cls_desc> get_cls_list() {
    return _cls_list;
}
