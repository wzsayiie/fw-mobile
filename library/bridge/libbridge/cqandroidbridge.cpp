#ifdef ANDROID

#include "cqandroidbridge.hh"
#include <android/log.h>

//use original api to print,
//cause it's possible that user log system depends on JNI context.

#define LOG(LEVEL, FORMAT)\
/**/    va_list args;\
/**/    va_start(args, format);\
/**/    __android_log_vprint(LEVEL , "zzz", FORMAT, args);\
/**/    va_end(args)

__printflike(1, 2) static void info (const char *format, ...) { LOG(ANDROID_LOG_INFO , format); }
__printflike(1, 2) static void error(const char *format, ...) { LOG(ANDROID_LOG_ERROR, format); }

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

CQValue CQJavaCallStatic(
    const char *classPath,
    const char *methodName,
    CQValue arg0,
    CQValue arg1,
    CQValue arg2,
    CQValue arg3
)
{
    JNIEnv *env = CQJavaGetEnv();
    if (env == nullptr) {
        error("try call static java method but java env is invalid");
        return CQValueNull;
    }

    jclass clazz = env->FindClass(classPath);
    if (JavaException(env)) {
        return CQValueNull;
    }

    jmethodID methodID = env->GetStaticMethodID(clazz, methodName, "(JJJJ)J");
    if (JavaException(env)) {
        return CQValueNull;
    }

    jlong ret = env->CallStaticLongMethod(clazz, methodID, arg0, arg1, arg2, arg3);
    if (JavaException(env)) {
        return CQValueNull;
    }

    return CQValueMake(ret);
}

#endif
