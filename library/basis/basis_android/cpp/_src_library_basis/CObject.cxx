#include "CObject.hh"
#include "cqjnihelper.hh"

static const int32_t JAVA_OBJECT_MAGIC = 0x4A415641; //"JAVA".

static void del_java_object(void *raw) {
    if (raw != nullptr) {
        cqJNIEnv::env()->DeleteGlobalRef((jobject)raw);
    }
}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CObject_retain
    (JNIEnv *env, jclass, jobject object, jstring cls)
{
    if (object != nullptr) {
        std::string name = cqJNIType::string(env, cls);
        void *raw = (void *)env->NewGlobalRef(object);
        cq_object *ptr = cq_object_retain(raw, name.c_str(), JAVA_OBJECT_MAGIC, del_java_object);
        return cqJNIType::jniPtr(env, ptr);
    }
    return nullptr;
}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CObject_raw
    (JNIEnv *env, jclass, jobject _j_raw)
{
    auto raw = cqJNIType::ptr<cq_object *>(env, _j_raw);
    if (raw == nullptr) {
        return nullptr;
    }

    if (cq_object_magic(raw) != JAVA_OBJECT_MAGIC) {
        //it's not a java object.
        return nullptr;
    }

    jobject object = (jobject)cq_object_raw(raw);
    return env->NewLocalRef(object);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CObject_listen
    (JNIEnv *env, jclass, jobject _j_object, jint event, jobject _j_block)
{
    auto object = cqJNIType::ptr<cq_object *>(env, _j_object);
    auto block  = cqJNIType::ptr<cq_block  *>(env, _j_block );

    cq_object_listen(object, (int32_t)event, block);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CObject_emit
    (JNIEnv *env, jclass, jobject _j_object, jint event)
{
    auto object = cqJNIType::ptr<cq_object *>(env, _j_object);
    cq_object_emit(object, (int32_t)event);
}
