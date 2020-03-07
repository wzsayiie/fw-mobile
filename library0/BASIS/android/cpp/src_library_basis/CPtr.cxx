#include "CPtr.hh"
#include "cqjnihelper.hh"

//NOTE: store c pointer with java long type.
static_assert(sizeof(jlong) >= sizeof(void *), "");

#define CLS_PATH "src/library/basis/CPtr"
CQ_JNI_CLASS(CPtr, CLS_PATH);

void *CPtr_valueFromObject(JNIEnv *env, jobject src) {
    if (env == nullptr) {
        return nullptr;
    }

    static jmethodID method = nullptr;
    cqJNIEnv::staticMethod(&method, env, CPtr(), "valueFromObject", "(L" CLS_PATH ";)J");

    return (void *)env->CallStaticLongMethod(CPtr(), method, src);
}

jobject CPtr_objectFromValue(JNIEnv *env, const void *src) {
    if (env == nullptr) {
        return nullptr;
    }

    static jmethodID method = nullptr;
    cqJNIEnv::staticMethod(&method, env, CPtr(), "objectFromValue", "(J)L" CLS_PATH ";");

    return env->CallStaticObjectMethod(CPtr(), method, (jlong)src);
}
