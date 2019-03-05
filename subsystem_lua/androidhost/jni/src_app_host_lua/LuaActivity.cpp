#include <jni.h>
#include "cqlogger.hh"
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

    I("Android Host: call main()");
    CQLuaVMDoString("main()");

    I("Android Host: post event AppCreate");
    CQLuaVMDoString("CQHost:onEvent(CQHost.Event.AppCreate)");

    I("Android Host: post event UILoad");
    CQLuaVMDoString("CQHost:onEvent(CQHost.Event.UILoad)");
}

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_lua_LuaActivity_handleStart(JNIEnv *, jobject) {

    I("Android Host: post event UIAppear");
    CQLuaVMDoString("CQHost:onEvent(CQHost.Event.UIAppear)");
}

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_lua_LuaActivity_handleStop(JNIEnv *, jobject) {

    I("Android Host: post event UIDisappear");
    CQLuaVMDoString("CQHost:onEvent(CQHost.Event.UIDisappear)");
}
