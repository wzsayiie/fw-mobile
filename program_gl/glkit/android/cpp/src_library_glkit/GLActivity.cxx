#include "cqjnihelper.hh"
#include "cqwindow.h"

static jclass clazz() {
    static jclass clazz = nullptr;
    if (clazz == nullptr) {
        cqJNIFindClass(&clazz, cqJNIGetEnv(), "src/library/glkit/GLActivity");
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

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_installInterfaces
    (JNIEnv *, jclass)
{
    _cq_interfaces interfaces = {nullptr}; {
        interfaces.create_window = create_window;
        interfaces.show_window = show_window;
    }
    _cq_init_interfaces(&interfaces);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowLoad
    (JNIEnv *, jclass, jlong wid)
{
    _cq_window_load(wid);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowAppear
    (JNIEnv *, jclass, jlong wid)
{
    _cq_window_appear(wid);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowDisappear
    (JNIEnv *, jclass, jlong wid)
{
    _cq_window_disappear(wid);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowUnload
    (JNIEnv *, jclass, jlong wid)
{
    _cq_window_unload(wid);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowScale
    (JNIEnv *, jclass, jlong wid, jfloat scale)
{
    _cq_window_scale(wid, scale);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowOrigin
    (JNIEnv *, jclass, jlong wid, jfloat x, jfloat y)
{
    _cq_window_origin(wid, x, y);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowSize
    (JNIEnv *, jclass, jlong wid, jfloat width, jfloat height)
{
    _cq_window_size(wid, width, height);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowUpdate
    (JNIEnv *, jclass, jlong wid)
{
    _cq_window_update (wid);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowGLPaint
    (JNIEnv *, jclass, jlong wid)
{
    _cq_window_glpaint(wid);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowPBegan
    (JNIEnv *, jclass, jlong wid, jfloat x, jfloat y)
{
    _cq_window_pbegan(wid, x, y);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowPMoved
    (JNIEnv *, jclass, jlong wid, jfloat x, jfloat y)
{
    _cq_window_pmoved(wid, x, y);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowPEnded
    (JNIEnv *, jclass, jlong wid, jfloat x, jfloat y)
{
    _cq_window_pended(wid, x, y);
}
