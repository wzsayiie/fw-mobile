#include "cqhostapi.h"
#include "cqjnihelper.hh"
#include <jni.h>

#define _F(n) extern "C" JNIEXPORT void JNICALL Java_src_app_host_cpp_CPPActivity_##n

_F(notifyDefaultWindowCreated)(JNIEnv *, jobject, jlong window_idx) {
    _cq_notify_default_window_created(window_idx);
}

_F(notifyLoad)(JNIEnv *, jobject, jlong idx) {_cq_notify_window_load(idx);}
_F(notifyShow)(JNIEnv *, jobject, jlong idx) {_cq_notify_window_show(idx);}
_F(notifyHide)(JNIEnv *, jobject, jlong idx) {_cq_notify_window_hide(idx);}

_F(notifyTouchBegan)(JNIEnv *, jobject, jlong idx, jfloat x, jfloat y) {_cq_notify_window_touch_began(idx, x, y);}
_F(notifyTouchMoved)(JNIEnv *, jobject, jlong idx, jfloat x, jfloat y) {_cq_notify_window_touch_moved(idx, x, y);}
_F(notifyTouchEnded)(JNIEnv *, jobject, jlong idx, jfloat x, jfloat y) {_cq_notify_window_touch_ended(idx, x, y);}

static jclass clazz() {
    static jclass clazz = nullptr;
    if (clazz == nullptr) {
        cqJNIFindClass(&clazz, cqJNIGetEnv(), "src/app/host/cpp/CPPActivity");
    }
    return clazz;
}

void _cq_window_set_back_color(int64_t window_idx, float r, float g, float b) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method(clazz(), &methodID, "_cq_window_set_back_color");

    method.push(window_idx);
    method.push(r);
    method.push(g);
    method.push(b);

    method.callVoid();
}

float _cq_window_get_width(int64_t window_idx) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method(clazz(), &methodID, "_cq_window_get_width");

    method.push(window_idx);

    return method.callFloat();
}

float _cq_window_get_height(int64_t window_idx) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method(clazz(), &methodID, "_cq_window_get_height");

    method.push(window_idx);

    return method.callFloat();
}

float _cq_window_get_screen_scale(int64_t window_idx) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method(clazz(), &methodID, "_cq_window_get_screen_scale");

    method.push(window_idx);

    return method.callFloat();
}
