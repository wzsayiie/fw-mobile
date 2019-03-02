#include <jni.h>
#include "cqluasource.hh"
#include "cqluavm.hh"

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_lua_LuaActivity_handleCreate(JNIEnv *env, jobject, jstring path) {

    std::string luaPath; {
        const char *copy = env->GetStringUTFChars(path, nullptr);
        luaPath.assign(copy);
        env->ReleaseStringUTFChars(path, copy);
    }

    CQLuaSourceUpdate(luaPath);
    CQLuaVMOpen(luaPath);

    CQLuaVMDoString("main()");
    CQLuaVMDoString("CQHost:onEvent(CQHost.Event.AppCreate)");
    CQLuaVMDoString("CQHost:onEvent(CQHost.Event.UILoad)");
}

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_lua_LuaActivity_handleStart(JNIEnv *, jobject) {

    CQLuaVMDoString("CQHost:onEvent(CQHost.Event.UIAppear)");
}

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_lua_LuaActivity_handleStop(JNIEnv *, jobject) {

    CQLuaVMDoString("CQHost:onEvent(CQHost.Event.UIDisappear)");
}
