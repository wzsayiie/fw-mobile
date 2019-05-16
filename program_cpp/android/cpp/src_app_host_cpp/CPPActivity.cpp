#include "cqosapi.h"
#include "cqjnihelper.hh"
#include <jni.h>

static jclass clazz() {
    static jclass clazz = nullptr;
    if (clazz == nullptr) {
        cqJNIFindClass(&clazz, cqJNIGetEnv(), "src/app/host/cpp/CPPActivity");
    }
    return clazz;
}

static void window_set_back_color(int64_t window_idx, float r, float g, float b) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method(clazz(), &methodID, "window_set_back_color");
    method.push(window_idx);
    method.push(r);
    method.push(g);
    method.push(b);
    method.callVoid();
}

static float window_get_width(int64_t window_idx) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method(clazz(), &methodID, "window_get_width");
    method.push(window_idx);
    return method.callFloat();
}

static float window_get_height(int64_t window_idx) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method(clazz(), &methodID, "window_get_height");
    method.push(window_idx);
    return method.callFloat();
}

static float window_get_screen_scale(int64_t window_idx) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method(clazz(), &methodID, "window_get_screen_scale");
    method.push(window_idx);
    return method.callFloat();
}

extern "C" JNIEXPORT void JNICALL Java_src_app_host_cpp_CPPActivity_onCreate
/**/(JNIEnv *, jobject, jlong index)
{
    _cq_install_window_set_back_color_handler(window_set_back_color);
    _cq_install_window_get_width_handler(window_get_width);
    _cq_install_window_get_height_handler(window_get_height);
    _cq_install_window_get_screen_scale_handler(window_get_screen_scale);

    _cq_notify_default_window_created(index);
    _cq_notify_window_load(index);
}

extern "C" JNIEXPORT void JNICALL Java_src_app_host_cpp_CPPActivity_onStart
/**/(JNIEnv *, jobject, jlong index)
{
    _cq_notify_window_show(index);
}

extern "C" JNIEXPORT void JNICALL Java_src_app_host_cpp_CPPActivity_onStop
/**/(JNIEnv *, jobject, jlong index)
{
    _cq_notify_window_hide(index);
}

extern "C" JNIEXPORT void JNICALL Java_src_app_host_cpp_CPPActivity_onTouchBegan
/**/(JNIEnv *, jobject, jlong index, jfloat x, jfloat y)
{
    _cq_notify_window_touch_began(index, x, y);
}

extern "C" JNIEXPORT void JNICALL Java_src_app_host_cpp_CPPActivity_onTouchMoved
/**/(JNIEnv *, jobject, jlong index, jfloat x, jfloat y)
{
    _cq_notify_window_touch_moved(index, x, y);
}

extern "C" JNIEXPORT void JNICALL Java_src_app_host_cpp_CPPActivity_onTouchEnded
/**/(JNIEnv *, jobject, jlong index, jfloat x, jfloat y)
{
    _cq_notify_window_touch_ended(index, x, y);
}
