#include <jni.h>
#include "cqhost_p.hh"
#include "cqlog.hh"

extern "C" void _main();

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_cpp_CPPActivity_handleCreate(JNIEnv *, jobject) {

    I("Android Host: call main()");
    _main();

    I("Android Host: post event AppCreate");
    CQHostOnEvent(CQHostEventAppCreate);

    I("Android Host: post event UILoad");
    CQHostOnEvent(CQHostEventUILoad);
}

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_cpp_CPPActivity_handleStart(JNIEnv *, jobject) {

    I("Android Host: post event UIAppear");
    CQHostOnEvent(CQHostEventUIAppear);
}

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_cpp_CPPActivity_handleStop(JNIEnv *, jobject) {

    I("Android Host: post event UIDisappear");
    CQHostOnEvent(CQHostEventUIDisappear);
}
