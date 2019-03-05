#ifdef ANDROID

#include "cqbridgejni.hh"
#include <android/log.h>

//NOTE:
//the bridge code does not print any log, because the log system will depends on the former.
//It will increase complexity if the bridge code print log.

static bool JavaException(JNIEnv *env) {
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        return true;
    } else {
        return false;
    }
}

static JavaVM *sJavaVM = nullptr;
static int sJNIVersion = 0;

jint JNI_OnLoad(JavaVM *vm, void *) {
    sJavaVM = vm;
    sJNIVersion = JNI_VERSION_1_6;
    return sJNIVersion;
}

JNIEnv *CQJavaGetEnv() {
    if (sJavaVM != nullptr) {
        JNIEnv *env = nullptr;
        sJavaVM->GetEnv((void **) &env, sJNIVersion);
        return env;
    } else {
        return nullptr;
    }
}

CQBridgeValue CQJavaCallStatic(
    const char *classPath,
    const char *methodName,
    CQBridgeValue arg0,
    CQBridgeValue arg1,
    CQBridgeValue arg2,
    CQBridgeValue arg3
)
{
    JNIEnv *env = CQJavaGetEnv();
    if (env == nullptr) {
        return CQBridgeValueNull;
    }

    jclass clazz = env->FindClass(classPath);
    if (JavaException(env)) {
        return CQBridgeValueNull;
    }

    jmethodID methodID = env->GetStaticMethodID(clazz, methodName, "(JJJJ)J");
    if (JavaException(env)) {
        return CQBridgeValueNull;
    }

    jlong ret = env->CallStaticLongMethod(clazz, methodID, arg0, arg1, arg2, arg3);
    if (JavaException(env)) {
        return CQBridgeValueNull;
    }

    return CQBridgeValueMake(ret);
}

#endif
