#include "cqlualibfoundation.h"
#include "cqfoundationarche.h"
#include "cqcppbasis.hh"

//host os:

static int32_t HostOS(lua_State *state) {
    
    CQ_IF_ON_ANDROID(return cq_lua_return_string(state, "android"));
    CQ_IF_ON_IOS    (return cq_lua_return_string(state, "ios"    ));
    CQ_IF_ON_WINDOWS(return cq_lua_return_string(state, "windows"));
    CQ_IF_ON_OSX    (return cq_lua_return_string(state, "osx"    ));
}

//log:

static int32_t LogInfo(lua_State *state) {
    const char *file = cq_lua_check_string(state, 1);
    int32_t     line = cq_lua_check_int32 (state, 2);
    const char *text = cq_lua_check_string(state, 3);
    
    cq_log_info(file, line, text);
    
    return cq_lua_return_void(state);
}

static int32_t LogError(lua_State *state) {
    const char *file = cq_lua_check_string(state, 1);
    int32_t     line = cq_lua_check_int32 (state, 2);
    const char *text = cq_lua_check_string(state, 3);
    
    cq_log_error(file, line, text);
    
    return cq_lua_return_void(state);
}

//app bundle resource:

static int32_t IOSBundlePath(lua_State *state) {
    const char *path = cq_ios_bundle_path();
    
    return cq_lua_return_string(state, path);
}

static int32_t IOSResourcePath(lua_State *state) {
    const char *name = cq_lua_check_string(state, 1);
    const char *type = cq_lua_check_string(state, 2);
    
    const char *path = cq_ios_resource_path(name, type);
    
    return cq_lua_return_string(state, path);
}

static int32_t AndroidCopyAsset(lua_State *state) {
    const char *from = cq_lua_check_string(state, 1);
    const char *to   = cq_lua_check_string(state, 2);
    
    bool success = cq_android_copy_asset(from, to);
    
    return cq_lua_return_bool(state, success);
}

//file access:

static int32_t DocumentDirectory(lua_State *state) {
    const char *directory = cq_document_directory();
    
    return cq_lua_return_string(state, directory);
}

static int32_t CachesDirectory(lua_State *state) {
    const char *directory = cq_caches_directory();
    
    return cq_lua_return_string(state, directory);
}

static int32_t TemporaryDirectory(lua_State *state) {
    const char *directory = cq_temporary_directory();
    
    return cq_lua_return_string(state, directory);
}

static int32_t DirectoryExists(lua_State *state) {
    const char *path = cq_lua_check_string(state, 1);
    bool success = cq_directory_exists(path);
    return cq_lua_return_bool(state, success);
}

static int32_t FileExists(lua_State *state) {
    const char *path = cq_lua_check_string(state, 1);
    bool success = cq_file_exists(path);
    return cq_lua_return_bool(state, success);
}

static int32_t CreateDirectory(lua_State *state) {
    const char *path  = cq_lua_check_string(state, 1);
    bool intermediate = cq_lua_check_bool  (state, 2);
    
    bool success = cq_create_directory(path, intermediate);
    
    return cq_lua_return_bool(state, success);
}

static int32_t RemovePath(lua_State *state) {
    const char *path = cq_lua_check_string(state, 1);
    cq_remove_path(path);
    return cq_lua_return_void(state);
}

static int32_t SubFiles(lua_State *state) {
    const char *path = cq_lua_check_string(state, 1);
    
    std::vector<std::string> files;
    cq_sub_files(path, cq_cpp_out(files));
    
    return cq_lua_return_str_list(state, cq_cpp_in(files));
}

//register

void cq_lua_load_lib_foundation() {
    
#define register_func(name) cq_lua_register_func(nullptr, #name, name)
    
    //host os:
    register_func(HostOS);
    
    //log:
    
    register_func(LogInfo );
    register_func(LogError);
    
    //app bundle resource:

    register_func(IOSBundlePath   );
    register_func(IOSResourcePath );
    register_func(AndroidCopyAsset);
    
    //file access:
    
    register_func(DocumentDirectory );
    register_func(CachesDirectory   );
    register_func(TemporaryDirectory);
    register_func(DirectoryExists   );
    register_func(FileExists        );
    register_func(CreateDirectory   );
    register_func(RemovePath        );
    register_func(SubFiles          );
}
