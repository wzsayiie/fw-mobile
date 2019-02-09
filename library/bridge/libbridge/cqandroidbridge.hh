#pragma once

#include "cbridgecore_p.h"
#include <jni.h>

JavaVM *CQJavaGetVM();
JNIEnv *CQJavaGetEnv();

CQType CQJavaCallStatic(
    const char *classPath,
    const char *methodName,
    CQType arg0,
    CQType arg1,
    CQType arg2,
    CQType arg3
);
