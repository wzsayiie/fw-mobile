#include "cqlualibfoundation.h"
#include "cqfoundationarche.h"

//host os:

static int32_t cq_host_os(lua_State *state) {
    
    CQ_IF_ON_ANDROID(return cq_lua_return_string(state, "android"));
    CQ_IF_ON_IOS    (return cq_lua_return_string(state, "ios"    ));
    CQ_IF_ON_WINDOWS(return cq_lua_return_string(state, "windows"));
    CQ_IF_ON_OSX    (return cq_lua_return_string(state, "osx"    ));
}

//app bundle resource:

static int32_t cq_ios_bundle_path(lua_State *state) {
    const char *path = cq_ios_bundle_path();
    
    return cq_lua_return_string(state, path);
}

static int32_t cq_ios_bundle_res_path(lua_State *state) {
    const char *name = cq_lua_check_string(state, 1);
    const char *type = cq_lua_check_string(state, 2);
    
    const char *path = cq_ios_bundle_res_path(name, type);
    
    return cq_lua_return_string(state, path);
}

static int32_t cq_andr_copy_asset(lua_State *state) {
    const char *from = cq_lua_check_string(state, 1);
    const char *to   = cq_lua_check_string(state, 2);
    
    bool success = cq_andr_copy_asset(from, to);
    
    return cq_lua_return_bool(state, success);
}

//log:

static int32_t cq_log_info(lua_State *state) {
    const char *file = cq_lua_check_string(state, 1);
    int32_t     line = cq_lua_check_int32 (state, 2);
    const char *text = cq_lua_check_string(state, 3);
    
    cq_log_info(file, line, text);
    
    return 0;
}

static int32_t cq_log_error(lua_State *state) {
    const char *file = cq_lua_check_string(state, 1);
    int32_t     line = cq_lua_check_int32 (state, 2);
    const char *text = cq_lua_check_string(state, 3);
    
    cq_log_error(file, line, text);
    
    return cq_lua_return_void(state);
}

//file access:

static int32_t cq_document_directory(lua_State *state) {
    const char *directory = cq_document_directory();
    
    return cq_lua_return_string(state, directory);
}

static int32_t cq_caches_directory(lua_State *state) {
    const char *directory = cq_caches_directory();
    
    return cq_lua_return_string(state, directory);
}

static int32_t cq_temporary_directory(lua_State *state) {
    const char *directory = cq_temporary_directory();
    
    return cq_lua_return_string(state, directory);
}

static int32_t cq_directory_exists(lua_State *state) {
    const char *path = cq_lua_check_string(state, 1);
    bool success = cq_directory_exists(path);
    return cq_lua_return_bool(state, success);
}

static int32_t cq_file_exists(lua_State *state) {
    const char *path = cq_lua_check_string(state, 1);
    bool success = cq_file_exists(path);
    return cq_lua_return_bool(state, success);
}

static int32_t cq_create_directory(lua_State *state) {
    const char *path  = cq_lua_check_string(state, 1);
    bool intermediate = cq_lua_check_bool  (state, 2);
    
    bool success = cq_create_directory(path, intermediate);
    
    return cq_lua_return_bool(state, success);
}

static int32_t cq_remove_path(lua_State *state) {
    const char *path = cq_lua_check_string(state, 1);
    cq_remove_path(path);
    return cq_lua_return_void(state);
}

static int32_t cq_open_dir(lua_State *state) {
    const char *path = cq_lua_check_string(state, 1);
    
    bool sucess = cq_open_dir(path);
    
    return cq_lua_return_bool(state, sucess);
}

static int32_t cq_read_dir(lua_State *state) {
    const char *item = cq_read_dir();
    
    return cq_lua_return_string(state, item);
}

static int32_t cq_close_dir(lua_State *state) {
    cq_close_dir();
    
    return cq_lua_return_void(state);
}

//register

void cq_lua_load_lib_foundation() {
    
#define register_func(name) cq_lua_register_func(#name, name)
    
    //host os:
    register_func(cq_host_os);
    
    //log:
    
    register_func(cq_log_info );
    register_func(cq_log_error);
    
    //app bundle resource:

    register_func(cq_ios_bundle_path    );
    register_func(cq_ios_bundle_res_path);
    register_func(cq_andr_copy_asset    );
    
    //file access:
    
    register_func(cq_document_directory );
    register_func(cq_caches_directory   );
    register_func(cq_temporary_directory);
    register_func(cq_directory_exists   );
    register_func(cq_file_exists        );
    register_func(cq_create_directory   );
    register_func(cq_remove_path        );
    
    register_func(cq_open_dir );
    register_func(cq_read_dir );
    register_func(cq_close_dir);
}
