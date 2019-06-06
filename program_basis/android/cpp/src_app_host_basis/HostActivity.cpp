#include "cqjnihelper.hh"
#include "cqwindow.h"

#define CLASS_PATH_STRING "src/app/host/basis/HostActivity"
#define CLASS_PATH_SYMBOL  src_app_host_basis_HostActivity

#define JM(name) M1(CLASS_PATH_SYMBOL, name)
#define M1(a, b) M2(a, b)
#define M2(a, b) extern "C" JNIEXPORT void JNICALL Java##_##a##_##b
#define JA(... ) (JNIEnv *, jobject, __VA_ARGS__)

static jclass clazz() {
    static jclass clazz = nullptr;
    if (clazz == nullptr) {
        cqJNIFindClass(&clazz, cqJNIGetEnv(), CLASS_PATH_STRING);
    }
    return clazz;
}

static int64_t create_window() {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method(clazz(), &methodID, "create_window");
    return method.callInt64();
}

static void show_window(int64_t wid) {
    static jmethodID methodID = nullptr;

    cqJNIStaticMethod method(clazz(), &methodID, "show_window");
    method.push(wid);
    return method.callVoid();
}

JM(installInterfaces)(JNIEnv *, jobject) {
    _cq_interfaces interfaces; {
        interfaces.create_window = create_window;
        interfaces.show_window = show_window;
    }
    _cq_install_interfaces(&interfaces);
}

JM(notifyWindowLoad     )JA(jlong i) {_cq_notify_window_load     (i);}
JM(notifyWindowAppear   )JA(jlong i) {_cq_notify_window_appear   (i);}
JM(notifyWindowDisappear)JA(jlong i) {_cq_notify_window_disappear(i);}
JM(notifyWindowUnload   )JA(jlong i) {_cq_notify_window_unload   (i);}

JM(notifyWindowScale )JA(jlong i, jfloat s /* --- */) {_cq_notify_window_scale (i, s   );}
JM(notifyWindowOrigin)JA(jlong i, jfloat x, jfloat y) {_cq_notify_window_origin(i, x, y);}
JM(notifyWindowSize  )JA(jlong i, jfloat w, jfloat h) {_cq_notify_window_size  (i, w, h);}

JM(notifyWindowGLDraw)JA(jlong i) {_cq_notify_window_gl_draw(i);}
JM(notifyWindowUpdate)JA(jlong i) {_cq_notify_window_update (i);}

JM(notifyWindowTouchBegan)JA(jlong i, jfloat x, jfloat y) {_cq_notify_window_touch_began(i, x, y);}
JM(notifyWindowTouchMoved)JA(jlong i, jfloat x, jfloat y) {_cq_notify_window_touch_moved(i, x, y);}
JM(notifyWindowTouchEnded)JA(jlong i, jfloat x, jfloat y) {_cq_notify_window_touch_ended(i, x, y);}
