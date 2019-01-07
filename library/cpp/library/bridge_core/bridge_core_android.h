#pragma once

#ifdef ANDROID
#ifdef __cplusplus
extern "C" <%
#endif

#include <jni.h>

//Bridge Initialization ->

JNIEXPORT void JNICALL Java_lib_bridge_Bridge_initialize(JNIEnv *env, jclass);

//JNI ->

//when JNI_OnLoad called, use this function to save java vm.
void BRGSetJavaVM(JavaVM *vm, int jniVersion);

//get java vm.
JavaVM *BRGGetJavaVM(void);

//get current thread's JNI environment.
JNIEnv *BRGGetJNIEnv(void);

#ifdef __cplusplus
%>
#endif
#endif //if defined ANDROID
