#include "cqhostapi.h"
#include "cqjnihelper.hh"
#include <jni.h>

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_cpp_CPPActivity_handleCreate(JNIEnv *, jobject, jlong window_idx) {
    _cq_notify_default_window_created(window_idx);
    _cq_notify_window_load(window_idx);
}

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_cpp_CPPActivity_handleStart(JNIEnv *, jobject, jlong window_idx) {
    _cq_notify_window_show(window_idx);
}

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_cpp_CPPActivity_handleStop(JNIEnv *, jobject, jlong window_idx) {
    _cq_notify_window_hide(window_idx);
}

static jclass find_class() {
    static jclass clazz = nullptr;
    if (clazz == nullptr) {
        cqJNIFindClass(&clazz, cqJNIGetEnv(), "src/app/host/cpp/CPPActivity");
    }
    return clazz;
}

void _cq_window_set_back_color(int64_t window_idx, float r, float g, float b) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method;
    method.select(find_class());
    method.select(&methodID, "_cq_window_set_back_color");

    method.push(window_idx);
    method.push(r);
    method.push(g);
    method.push(b);

    method.callVoid();
}

float _cq_window_get_width(int64_t window_idx) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method;
    method.select(find_class());
    method.select(&methodID, "_cq_window_get_width");

    method.push(window_idx);

    return method.callFloat();
}

float _cq_window_get_height(int64_t window_idx) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method;
    method.select(find_class());
    method.select(&methodID, "_cq_window_get_height");

    method.push(window_idx);

    return method.callFloat();
}

float _cq_window_get_screen_scale(int64_t window_idx) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method;
    method.select(find_class());
    method.select(&methodID, "_cq_window_get_screen_scale");

    method.push(window_idx);

    return method.callFloat();
}
