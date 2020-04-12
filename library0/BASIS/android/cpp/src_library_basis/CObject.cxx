#include "CObject.hh"
#include "cqjnihelper.hh"

static const int32_t JAVA_OBJECT_MAGIC = 0x4A415641; //"JAVA".

static void release_raw_java(void *raw) {
    if (raw != nullptr) {
        cqJNIEnv::env()->DeleteGlobalRef((jobject)raw);
    }
}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CObject_retain
    (JNIEnv *env, jclass, jobject object, jstring cls)
{
    if (object == nullptr) {
        return nullptr;
    }

    void *raw = (void *)env->NewGlobalRef(object);
    cq_obj *ptr = cq_obj_retain_raw(raw, release_raw_java);

    std::string name = cqJNIType::string(env, cls);
    if (!name.empty()) {
        cq_obj_set_cls(ptr, name.c_str());
    }
    cq_obj_set_magic(ptr, JAVA_OBJECT_MAGIC);

    return cqJNIType::jniPtr(env, ptr);
}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CObject_raw
    (JNIEnv *env, jclass, jobject _ptr)
{
    auto ptr = cqJNIType::ptr<cq_obj *>(env, _ptr);
    if (ptr == nullptr) {
        return nullptr;
    }

    if (cq_obj_magic(ptr) != JAVA_OBJECT_MAGIC) {
        //it's not a java object.
        return nullptr;
    }

    jobject object = (jobject)cq_obj_raw(ptr);
    return env->NewLocalRef(object);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CObject_emit
    (JNIEnv *env, jclass, jobject _ptr, jint event)
{
    auto ptr = cqJNIType::ptr<cq_obj *>(env, _ptr);
    if (ptr != nullptr) {
        cq_obj_emit_event(ptr, (int32_t)event);
    }
}
