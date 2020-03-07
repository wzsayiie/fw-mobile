#pragma once

#include <jni.h>

void   *CPtr_valueFromObject(JNIEnv *env, jobject     src);
jobject CPtr_objectFromValue(JNIEnv *env, const void *src);
