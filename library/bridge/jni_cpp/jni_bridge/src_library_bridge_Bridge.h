#pragma once

#include "bridge_core.h"
#include <jni.h>

JavaVM *BRGGetJavaVM();
JNIEnv *BRGGetJNIEnv();
