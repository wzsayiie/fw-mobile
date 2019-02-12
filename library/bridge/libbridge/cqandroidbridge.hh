#pragma once

#include "cqbridgecore_p.h"
#include <jni.h>

JavaVM *CQJavaGetVM();
JNIEnv *CQJavaGetEnv();

CQValue CQJavaCallStatic(
    const char *classPath,
    const char *methodName,
    CQValue arg0,
    CQValue arg1,
    CQValue arg2,
    CQValue arg3
);
