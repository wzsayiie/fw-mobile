#ifdef ANDROID

#include "cqbridgejni.hh"
#include <android/log.h>

//use original api to print,
//cause it's possible that user log system depends on JNI context.

__printflike(1, 2) static void info(const char *format, ...) {
    va_list args;
    va_start(args, format);
    __android_log_vprint(ANDROID_LOG_INFO, "zzz", format, args);
    va_end(args);
}

__printflike(1, 2) static void error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    __android_log_vprint(ANDROID_LOG_ERROR, "zzz", format, args);
    va_end(args);
}

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

    if (sJavaVM != nullptr) {
        info("set java vm %p", sJavaVM);
    } else {
        error("set empty java vm");
    }

    return sJNIVersion;
}

JavaVM *CQJavaGetVM() {
    if (sJavaVM == nullptr) {
        error("java vm didn't set");
    }
    return sJavaVM;
}

JNIEnv *CQJavaGetEnv() {
    JNIEnv *env = nullptr;
    jint result = CQJavaGetVM()->GetEnv((void **)&env, sJNIVersion);
    if (result != JNI_OK) {
        error("didn't get java env, code %d", result);
        return nullptr;
    }

    return env;
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
        error("try call static java method but java env is invalid");
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
