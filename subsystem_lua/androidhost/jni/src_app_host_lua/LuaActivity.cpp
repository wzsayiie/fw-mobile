#include <jni.h>
#include "cqjnihelper.hh"
#include "cq_lua_source.h"
#include "cq_lua_vm.h"

#define J(func) Java_src_app_host_lua_LuaActivity_##func

CQ_JNI(void) J(onCreate)(JNIEnv *, jobject, jstring path, jlong index) {
}

CQ_JNI(void) J(onStart)(JNIEnv *, jobject, jlong index) {
}

CQ_JNI(void) J(onStop)(JNIEnv *, jobject, jlong index) {
}
