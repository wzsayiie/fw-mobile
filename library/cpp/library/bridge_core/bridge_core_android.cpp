#ifdef ANDROID

#include "bridge_core_android.h"
#include <android/log.h>

//use original api to print,
//cause it's possible that user log system depends on JNI context.
static void info (const char *text) { __android_log_print(ANDROID_LOG_INFO, "iii", "%s", text); }
static void error(const char *text) { __android_log_print(ANDROID_LOG_INFO, "eee", "%s", text); }

static JavaVM *sJavaVM = NULL;
static int sJniVersion = 0;

void BRGSetJavaVM(JavaVM *vm, int jniVersion) {
    sJavaVM = vm;
    sJniVersion = jniVersion;

    if (sJavaVM != NULL) {
        info("set java vm");
    } else {
        error("set empty java vm");
    }
}

JavaVM *BRGGetJavaVM() {
    if (sJavaVM == NULL) {
        error("java vm didn't set");
    }
    return sJavaVM;
}

JNIEnv *BRGGetJNIEnv() {
    JNIEnv *env = NULL;
    BRGGetJavaVM()->GetEnv((void **)env, sJniVersion);
    return env;
}

#endif //if defined ANDROID
