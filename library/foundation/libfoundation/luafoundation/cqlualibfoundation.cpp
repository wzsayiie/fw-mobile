#include "cqlualibfoundation.h"
#include "cqfoundationarche.h"

//log:

static int32_t log_info(lua_State *state) {
    const char *file = cq_lua_check_string(state, 1);
    int32_t     line = cq_lua_check_int32 (state, 2);
    const char *text = cq_lua_check_string(state, 3);
    
    cq_log_info(file, line, text);
    
    return 0;
}

static int32_t log_error(lua_State *state) {
    const char *file = cq_lua_check_string(state, 1);
    int32_t     line = cq_lua_check_int32 (state, 2);
    const char *text = cq_lua_check_string(state, 3);
    
    cq_log_error(file, line, text);
    
    return cq_lua_return_void(state);
}

//file access:

static int32_t document_directory(lua_State *state) {
    const char *directory = cq_document_directory();
    
    return cq_lua_return_string(state, directory);
}

static int32_t caches_directory(lua_State *state) {
    const char *directory = cq_caches_directory();
    
    return cq_lua_return_string(state, directory);
}

static int32_t temporary_directory(lua_State *state) {
    const char *directory = cq_temporary_directory();
    
    return cq_lua_return_string(state, directory);
}

static int32_t directory_exists(lua_State *state) {
    const char *path = cq_lua_check_string(state, 1);
    bool success = cq_directory_exists(path);
    return cq_lua_return_bool(state, success);
}

static int32_t file_exists(lua_State *state) {
    const char *path = cq_lua_check_string(state, 1);
    bool success = cq_file_exists(path);
    return cq_lua_return_bool(state, success);
}

static int32_t create_directory(lua_State *state) {
    const char *path  = cq_lua_check_string(state, 1);
    bool intermediate = cq_lua_check_bool  (state, 2);
    
    bool success = cq_create_directory(path, intermediate);
    
    return cq_lua_return_bool(state, success);
}

static int32_t remove_path(lua_State *state) {
    const char *path = cq_lua_check_string(state, 1);
    cq_remove_path(path);
    return cq_lua_return_void(state);
}

//register

void cq_lua_load_lib_foundation() {
    
    cq_lua_register_func("cq_log_info" , log_info );
    cq_lua_register_func("cq_log_error", log_error);
    
    cq_lua_register_func("cq_document_directory" , document_directory );
    cq_lua_register_func("cq_caches_directory"   , caches_directory   );
    cq_lua_register_func("cq_temporary_directory", temporary_directory);
    cq_lua_register_func("cq_directory_exists"   , directory_exists   );
    cq_lua_register_func("cq_file_exists"        , file_exists        );
    cq_lua_register_func("cq_create_directory"   , create_directory   );
    cq_lua_register_func("cq_remove_path"        , remove_path        );
}
