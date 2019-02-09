#include <jni.h>
#include "cqhost_p.hh"

extern "C" void _main();

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_CPPCarrierActivity_handleCreate(JNIEnv *, jobject) {
    _main();
    CQHostOnEvent(CQHostEventAppCreate);
    CQHostOnEvent(CQHostEventUILoad);
}

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_CPPCarrierActivity_handleStart(JNIEnv *, jobject) {
    CQHostOnEvent(CQHostEventUIAppear);
}

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_CPPCarrierActivity_handleStop(JNIEnv *, jobject) {
    CQHostOnEvent(CQHostEventUIDisappear);
}
