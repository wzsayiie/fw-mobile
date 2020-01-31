#pragma once

//CLASS DEFINISION LANGUAGE.

//specify library type:
//
//| def_local_lib();
//
void def_local_lib();
void def_cpp_lib();

//specify location of generated files:
//
//| cpp_header("foundation.hh");
//| cpp_source("foundation.cpp");
//
void java_source(const char *dir );
void java_native(const char *file);
void objc_header(const char *file);
void objc_source(const char *file);
void w32_header (const char *file);
void w32_source (const char *file);
void cpp_header (const char *file);
void cpp_source (const char *file);
void lua_cpp_h  (const char *file);
void lua_cpp_s  (const char *file);
void lua_script (const char *file);

//specify prefix of classes:
//
//| java_pkg   ("src.library.foundation");
//| objc_prefix("CQ");
//| w32_prefix ("cqw32");
//| cpp_prefix ("cq");
//| lua_prefix ("cq");
//
void java_pkg   (const char *pkg   );
void objc_prefix(const char *prefix);
void w32_prefix (const char *prefix);
void cpp_prefix (const char *prefix);
void lua_prefix (const char *prefix);

//specify lua script load function for c++:
//
//|  lua_load_f("cq_lua_lib_load_foundation");
//
void lua_load_f(const char *name);

enum _type_id {
    _type_id_null,
    
    _type_id_bool,
    
    _type_id_int8 ,
    _type_id_int16,
    _type_id_int32,
    _type_id_int64,
    
    _type_id_float ,
    _type_id_double,
    
    _type_id_string,
    
    //byte block data.
    //like vector<uint8_t> in c++ and byte[] in java.
    _type_id_bytes,
    
    _type_id_cls,
};

struct _type {
    _type() {
        iden = _type_id_null;
        name = "";
    }
    _type(_type_id i, const char *n) {
        iden = i;
        name = n;
    }
    
    _type_id iden;
    
    //if $iden is a cls, use $name specify the class name.
    const char *name;
};

//available basic data types:
static _type Void  (_type_id_null  , "");
static _type Bool  (_type_id_bool  , "");
static _type Int8  (_type_id_int8  , "");
static _type Int16 (_type_id_int16 , "");
static _type Int32 (_type_id_int32 , "");
static _type Int64 (_type_id_int64 , "");
static _type Float (_type_id_float , "");
static _type Double(_type_id_double, "");
static _type String(_type_id_string, "");
static _type Bytes (_type_id_bytes , "");

//use keyword "cls" to declare a class:
//
//| cls(FileManager);
//
struct _cls : _type {
    _cls(const char *name): _type(_type_id_cls, name) {}
};

#define cls(name) _cls name(""#name)

//use keyword "def" to define a class that does not need to be implemented:
//
//| def(FileManager) {
//| }
//
struct _def : _type {
    _def(const char *name);
};

#define def(name) _def name(""#name);

//use keyword "func" to define a function:
//
//| def(FileManager); {
//|     func("createDirectory")("path", String) >> Bool;
//| }
//
//use "statik" to specify a function is class function:
//
//| def(FileManager); {
//|     statik func("defaultManager")() >> FileManager;
//| }

void _statik();

#define statik _statik();

struct _func_back {

    _func_back operator()(
    );
    _func_back operator()(
        const char *name1, _type type1
    );
    _func_back operator()(
        const char *name1, _type type1,
        const char *name2, _type type2
    );
    _func_back operator()(
        const char *name1, _type type1,
        const char *name2, _type type2,
        const char *name3, _type type3
    );
    _func_back operator()(
        const char *name1, _type type1,
        const char *name2, _type type2,
        const char *name3, _type type3,
        const char *name4, _type type4
    );
    
    void operator>>(_type type);
};

_func_back func(const char *name);
