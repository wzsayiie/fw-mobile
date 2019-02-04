#include <jni.h>
#include "chost_p.h"

extern "C" void _main();

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_CPPCarrierActivity_handleCreate(JNIEnv *, jobject) {
    _main();
    CHostOnEvent(CHostEventAppCreate);
    CHostOnEvent(CHostEventUILoad);
}

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_CPPCarrierActivity_handleStart(JNIEnv *, jobject) {
    CHostOnEvent(CHostEventUIAppear);
}

extern "C" JNIEXPORT void JNICALL
Java_src_app_host_CPPCarrierActivity_handleStop(JNIEnv *, jobject) {
    CHostOnEvent(CHostEventUIDisappear);
}
