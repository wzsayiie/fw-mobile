#include "CBridge.hh"
#include "cqjnihelper.hh"

static const int32_t JAVA_OBJECT_MAGIC = 0x4A415641; //"JAVA".

static void del_bridge(void *raw) {
    if (raw != nullptr) {
        cqJNIEnv::env()->DeleteGlobalRef((jobject)raw);
    }
}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CBridge_retainRaw
    (JNIEnv *env, jclass, jobject object, jstring cls)
{
    if (object != nullptr) {
        std::string name = cqJNIType::string(env, cls);
        void *raw = (void *)env->NewGlobalRef(object);
        cq_bridge *ptr = cq_bridge_retain_raw(raw, name.c_str(), JAVA_OBJECT_MAGIC, del_bridge);
        return cqJNIType::jniPtr(env, ptr);
    }
    return nullptr;
}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CBridge_retain
    (JNIEnv *env, jclass, jobject _bridge)
{
    auto bridge = cqJNIType::ptr<cq_bridge *>(env, _bridge);
    cq_bridge_retain(bridge);
    return _bridge;
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CBridge_release
    (JNIEnv *env, jclass, jobject _bridge)
{
    auto bridge = cqJNIType::ptr<cq_bridge *>(env, _bridge);
    cq_bridge_release(bridge);
}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CBridge_raw
    (JNIEnv *env, jclass, jobject _raw)
{
    auto raw = cqJNIType::ptr<cq_bridge *>(env, _raw);
    if (raw == nullptr) {
        return nullptr;
    }

    if (cq_bridge_magic(raw) != JAVA_OBJECT_MAGIC) {
        //it's not a java object.
        return nullptr;
    }

    jobject object = (jobject)cq_bridge_raw(raw);
    return env->NewLocalRef(object);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CBridge_listen
    (JNIEnv *env, jclass, jobject _bridge, jint event, jobject _block)
{
    auto bridge = cqJNIType::ptr<cq_bridge *>(env, _bridge);
    auto block  = cqJNIType::ptr<cq_block  *>(env, _block );

    cq_bridge_listen(bridge, (int32_t)event, block);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CBridge_emit
    (JNIEnv *env, jclass, jobject _bridge, jint event)
{
    auto bridge = cqJNIType::ptr<cq_bridge *>(env, _bridge);
    cq_bridge_emit(bridge, (int32_t)event);
}
