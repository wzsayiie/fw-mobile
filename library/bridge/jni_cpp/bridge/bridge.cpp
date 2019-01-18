#include "bridge.h"
#include <android/log.h>

//use original api to print,
//cause it's possible that user log system depends on JNI context.
static void info (const char *text) { __android_log_print(ANDROID_LOG_INFO, "zzz", "%s", text); }
static void error(const char *text) { __android_log_print(ANDROID_LOG_INFO, "zzz", "%s", text); }

static JavaVM *sJavaVM = NULL;
static int sJNIVersion = 0;

jint JNI_OnLoad(JavaVM *vm, void *) {
    sJavaVM = vm;
    sJNIVersion = JNI_VERSION_1_6;

    if (sJavaVM != NULL) {
        info("set java vm");
    } else {
        error("set empty java vm");
    }

    return sJNIVersion;
}

JavaVM *BRGGetJavaVM() {
    if (sJavaVM == NULL) {
        error("java vm didn't set");
    }
    return sJavaVM;
}

JNIEnv *BRGGetJNIEnv() {
    if (sJavaVM == NULL) {
        error("java vm is null");
        return NULL;
    }

    JNIEnv *env = NULL;
    jint result = BRGGetJavaVM()->GetEnv((void **)env, sJNIVersion);
    if (result != JNI_OK) {
        error("didn't get java env");
        return NULL;
    }

    return env;
}
