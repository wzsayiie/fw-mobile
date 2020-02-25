#include "cqjnihelper.hh"
#include "cqwnd.h"

CQ_JNI_CLASS(GLActivity, "src/library/glkit/GLActivity");

static float wnd_scale() {
    CQ_JNI_STATIC_METHOD(GLActivity, method, "windowScale");
    return method.fn<float>();
}

static int64_t new_wnd() {
    CQ_JNI_STATIC_METHOD(GLActivity, method, "createWindow");
    return method.fn<int64_t>();
}

static void show_wnd(int64_t wid) {
    CQ_JNI_STATIC_METHOD(GLActivity, method, "showWindow");
    return method.fn<void>(wid);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_initWindowPort
    (JNIEnv *, jclass)
{
    _cq_wndport port = {nullptr}; {
        port.wnd_scale = wnd_scale;
        port.new_wnd   = new_wnd;
        port.show_wnd  = show_wnd;
    }
    _cq_init_wndport(&port);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowLoad
    (JNIEnv *, jclass, jlong wid)
{
    _cq_wnd_load(wid);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowAppear
    (JNIEnv *, jclass, jlong wid)
{
    _cq_wnd_appear(wid);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowDisappear
    (JNIEnv *, jclass, jlong wid)
{
    _cq_wnd_disappear(wid);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowUnload
    (JNIEnv *, jclass, jlong wid)
{
    _cq_wnd_unload(wid);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowOrigin
    (JNIEnv *, jclass, jlong wid, jfloat x, jfloat y)
{
    _cq_wnd_origin(wid, x, y);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowSize
    (JNIEnv *, jclass, jlong wid, jfloat width, jfloat height)
{
    _cq_wnd_size(wid, width, height);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowUpdate
    (JNIEnv *, jclass, jlong wid)
{
    _cq_wnd_update(wid);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowGLDraw
    (JNIEnv *, jclass, jlong wid)
{
    _cq_wnd_gldraw(wid);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowPBegan
    (JNIEnv *, jclass, jlong wid, jfloat x, jfloat y)
{
    _cq_wnd_pbegan(wid, x, y);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowPMoved
    (JNIEnv *, jclass, jlong wid, jfloat x, jfloat y)
{
    _cq_wnd_pmoved(wid, x, y);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_glkit_GLActivity_windowPEnded
    (JNIEnv *, jclass, jlong wid, jfloat x, jfloat y)
{
    _cq_wnd_pended(wid, x, y);
}
