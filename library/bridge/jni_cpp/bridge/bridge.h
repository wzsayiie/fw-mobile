#pragma once

# if !defined(__cplusplus)
#   error "this header should be include by c++ source"
# endif

#include <jni.h>

JavaVM *BRGGetJavaVM();
JNIEnv *BRGGetJNIEnv();
