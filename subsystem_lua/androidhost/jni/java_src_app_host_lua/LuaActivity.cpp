#include <jni.h>
#include "cqjnihelper.hh"
#include "cq_lua_source.h"
#include "cq_lua_vm.h"

extern "C" JNIEXPORT void JNICALL Java_src_app_host_lua_LuaActivity_onCreate
/**/(JNIEnv *, jobject, jstring path, jlong index) {
}

extern "C" JNIEXPORT void JNICALL Java_src_app_host_lua_LuaActivity_onStart
/**/(JNIEnv *, jobject, jlong index) {
}

extern "C" JNIEXPORT void JNICALL Java_src_app_host_lua_LuaActivity_onStop
/**/(JNIEnv *, jobject, jlong index) {
}
