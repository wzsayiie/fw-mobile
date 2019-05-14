#include <jni.h>
#include "cqjnihelper.hh"

#import "cqluasource.h"
#import "cqluavm.h"
#import "cqlualibfoundation.h"
#import "cqlualibsubsystem.h"
#import "cqlualibuikit.h"

extern "C" JNIEXPORT void JNICALL Java_src_app_host_lua_LuaActivity_onCreate
/**/(JNIEnv *, jobject, jlong index) {

    cq_lua_open_vm();
    cq_lua_load_lib_foundation();
    cq_lua_load_lib_subsystem();
    cq_lua_load_lib_uikit();

    cq_lua_run_scripts();
}

extern "C" JNIEXPORT void JNICALL Java_src_app_host_lua_LuaActivity_onStart
/**/(JNIEnv *, jobject, jlong index) {
}

extern "C" JNIEXPORT void JNICALL Java_src_app_host_lua_LuaActivity_onStop
/**/(JNIEnv *, jobject, jlong index) {
}
