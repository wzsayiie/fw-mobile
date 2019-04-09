#include "cqhostapi.h"
#include "cqjnihelper.hh"
#include <jni.h>

#define J(n) Java_src_app_host_cpp_CPPActivity_##n
#define A JNIEnv *, jobject

CQ_JNI(void) J(notifyDefaultWindowCreated)(A, jlong w) {_cq_notify_default_window_created(w);}

CQ_JNI(void) J(notifyLoad)(A, jlong w) {_cq_notify_window_load(w);}
CQ_JNI(void) J(notifyShow)(A, jlong w) {_cq_notify_window_show(w);}
CQ_JNI(void) J(notifyHide)(A, jlong w) {_cq_notify_window_hide(w);}

CQ_JNI(void) J(notifyTouchBegan)(A, jlong w, jfloat x, jfloat y) {_cq_notify_window_touch_began(w, x, y);}
CQ_JNI(void) J(notifyTouchMoved)(A, jlong w, jfloat x, jfloat y) {_cq_notify_window_touch_moved(w, x, y);}
CQ_JNI(void) J(notifyTouchEnded)(A, jlong w, jfloat x, jfloat y) {_cq_notify_window_touch_ended(w, x, y);}

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
