#pragma once

#include "bridge_core.h"
#include <jni.h>

JavaVM *BRGJavaGetVM();
JNIEnv *BRGJavaGetEnv();

BRGType BRGJavaCallStatic(
    const char *classPath,
    const char *methodName,
    BRGType arg0,
    BRGType arg1,
    BRGType arg2,
    BRGType arg3
);
