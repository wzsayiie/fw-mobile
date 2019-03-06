#include "cqbridgejni.hh"

extern "C" JNIEXPORT jint JNICALL Java_src_library_bridge_BridgeValue_getInt
    (JNIEnv *, jclass, jlong handle)
{
    CQBridgeValue value = CQBridgeValueMake(handle);
    jint raw = CQBridgeGetInt32(value);
    return raw;
}

extern "C" JNIEXPORT jstring JNICALL Java_src_library_bridge_BridgeValue_getString
    (JNIEnv *env, jclass, jlong handle)
{
    CQBridgeValue value = CQBridgeValueMake(handle);
    const char *bytes = CQBridgeStringValue(value);
    jstring str = env->NewStringUTF(bytes);
    return str;
}
