#include "src_library_bridge_Bridge.h"
#include <android/log.h>

//use original api to print,
//cause it's possible that user log system depends on JNI context.
static void info (const char *text) { __android_log_print(ANDROID_LOG_INFO, "zzz", "%s", text); }
static void error(const char *text) { __android_log_print(ANDROID_LOG_INFO, "zzz", "%s", text); }

static JavaVM *sJavaVM = nullptr;
static int sJNIVersion = 0;

jint JNI_OnLoad(JavaVM *vm, void *) {
    sJavaVM = vm;
    sJNIVersion = JNI_VERSION_1_6;

    if (sJavaVM != nullptr) {
        info("set java vm");
    } else {
        error("set empty java vm");
    }

    return sJNIVersion;
}

JavaVM *BRGGetJavaVM() {
    if (sJavaVM == nullptr) {
        error("java vm didn't set");
    }
    return sJavaVM;
}

JNIEnv *BRGGetJNIEnv() {
    if (sJavaVM == nullptr) {
        error("java vm is nullptr");
        return nullptr;
    }

    JNIEnv *env = nullptr;
    jint result = BRGGetJavaVM()->GetEnv((void **)env, sJNIVersion);
    if (result != JNI_OK) {
        error("didn't get java env");
        return nullptr;
    }

    return env;
}
