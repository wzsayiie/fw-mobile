#include "CPtr.hh"
#include "cqjnihelper.hh"

//NOTE: store c pointer with java long type.
static_assert(sizeof(jlong) >= sizeof(void *), "");

#define CLS_PATH "src/library/basis/CPtr"
CQ_JNI_CLASS(CPtr, CLS_PATH);

void *CPtr_valueFromObject(jobject object) {
    JNIEnv *env = cqJNIEnv::env();
    jclass  cls = CPtr();

    static jmethodID method = nullptr;
    cqJNIEnv::staticMethod(&method, env, cls, "valueFromObject", "(L" CLS_PATH ";)J");

    return (void *)env->CallStaticLongMethod(cls, method, object);
}

jobject CPtr_objectFromValue(const void *value) {
    JNIEnv *env = cqJNIEnv::env();
    jclass  cls = CPtr();

    static jmethodID method = nullptr;
    cqJNIEnv::staticMethod(&method, env, cls, "objectFromValue", "(J)L" CLS_PATH ";");

    return env->CallStaticObjectMethod(cls, method, (jlong)value);
}
