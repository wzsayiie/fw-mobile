#include <jni.h>
#include "cqhostapi.h"
#include "cqlog.hh"

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_cpp_CPPActivity_handleCreate(JNIEnv *, jobject) {
}

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_cpp_CPPActivity_handleStart(JNIEnv *, jobject) {
}

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_cpp_CPPActivity_handleStop(JNIEnv *, jobject) {
}

cq_window *cq_window_create(void) {
    return nullptr;
}

void cq_window_load(cq_window *window) {
}

void cq_window_set_back_color(cq_window *window, float r, float g, float b) {
}

float cq_window_get_width(cq_window *window) {
    return 0;
}

float cq_window_get_height(cq_window *window) {
    return 0;
}

float cq_window_get_screen_scale(cq_window *window) {
    return 0;
}
