#pragma once

#include "cqbridgecore.h"
#include <jni.h>

CQBridgeValue CQJavaCallStatic(
    const char *classPath,
    const char *methodName,
    CQBridgeValue arg0,
    CQBridgeValue arg1,
    CQBridgeValue arg2,
    CQBridgeValue arg3
);
