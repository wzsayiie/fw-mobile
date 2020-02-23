#include "CPtr.hh"
#include "cqjnihelper.hh"

//NOTE: store c pointer with java long type.
static_assert(sizeof(jlong) >= sizeof(void *), "");

#define CLS "src/library/basis/CPtr"

static jclass clazz() {
    static jclass clazz = nullptr;
    if (clazz == nullptr) {
        cqJNIFindClass(&clazz, cqJNIGetEnv(), CLS);
    }
    return clazz;
}

void *CPtr_valueFromObject(jobject object) {
    JNIEnv *env = cqJNIGetEnv();
    jclass  cls = clazz();

    static jmethodID method = nullptr;
    cqJNIGetStatic(&method, env, cls, "valueFromObject", "(L" CLS ";)J");

    return (void *)env->CallStaticLongMethod(cls, method, object);
}

jobject CPtr_objectFromValue(const void *value) {
    JNIEnv *env = cqJNIGetEnv();
    jclass  cls = clazz();

    static jmethodID method = nullptr;
    cqJNIGetStatic(&method, env, cls, "objectFromValue", "(J)L" CLS ";");

    return env->CallStaticObjectMethod(cls, method, (jlong)value);
}
