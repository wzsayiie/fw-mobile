#ifdef ANDROID

#include "bridge_android.h"
#include <android/log.h>

//use original api to print,
//cause it's possible that user log system depends on JNI context.

#define LOG(LEVEL, FORMAT)\
/**/    va_list args;\
/**/    va_start(args, format);\
/**/    __android_log_vprint(LEVEL , "zzz", FORMAT, args);\
/**/    va_end(args)

static void info (const char *format, ...) __printflike(1, 2) { LOG(ANDROID_LOG_INFO , format); }
static void error(const char *format, ...) __printflike(1, 2) { LOG(ANDROID_LOG_ERROR, format); }

#undef LOG

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

JavaVM *BRGJavaGetVM() {
    if (sJavaVM == nullptr) {
        error("java vm didn't set");
    }
    return sJavaVM;
}

JNIEnv *BRGJavaGetEnv() {
    JNIEnv *env = nullptr;
    jint result = BRGJavaGetVM()->GetEnv((void **)&env, sJNIVersion);
    if (result != JNI_OK) {
        error("didn't get java env, code %d", result);
        return nullptr;
    }

    return env;
}

BRGType BRGJavaCallStatic(
    const char *classPath,
    const char *methodName,
    BRGType arg0,
    BRGType arg1,
    BRGType arg2,
    BRGType arg3
)
{
    JNIEnv *env = BRGJavaGetEnv();
    if (env == nullptr) {
        error("try call static java method but java env is invalid");
        return BRGTypeNULL;
    }

    jclass clazz = env->FindClass(classPath);
    if (JavaException(env)) {
        return BRGTypeNULL;
    }

    jmethodID methodID = env->GetStaticMethodID(clazz, methodName, "(JJJJ)J");
    if (JavaException(env)) {
        return BRGTypeNULL;
    }

    BRGType ret;
    ret.handle = env->CallStaticLongMethod(clazz, methodID, arg0, arg1, arg2, arg3);
    if (JavaException(env)) {
        return BRGTypeNULL;
    }

    return ret;
}

#endif
