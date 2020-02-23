#pragma once

#include <jni.h>

void   *CPtr_valueFromObject(jobject     object);
jobject CPtr_objectFromValue(const void *value );
