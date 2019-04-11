#include <jni.h>
#include "cqlog.hh"
#include "cq_lua_source.h"
#include "cq_lua_vm.h"

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_lua_LuaActivity_handleCreate(JNIEnv *env, jobject, jstring path) {
}

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_lua_LuaActivity_handleStart(JNIEnv *, jobject) {
}

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_lua_LuaActivity_handleStop(JNIEnv *, jobject) {
}
