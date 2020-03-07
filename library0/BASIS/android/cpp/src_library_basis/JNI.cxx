#include "JNI.hh"
#include "cqjnihelper.hh"

CQ_JNI_CLASS(JNI, "src/library/basis/JNI");

//runnable:

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_JNI_run
    (JNIEnv *env, jclass, jobject _runnable, jobject _data)
{
    auto runnable = cqJNIType::ptr<cq_runnable>(env, _runnable);
    auto data     = cqJNIType::ptr<void *>(env, _data);

    if (runnable != nullptr) {
        runnable(data);
    }
}

//data structure:

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_JNI_makeBytesSuck
    (JNIEnv *env, jclass, jobject _in)
{
    static jmethodID method = nullptr;
    cqJNIEnv::staticMethod(&method, env, JNI(), "onBytesSuck", "([B)V");

    auto in = cqJNIType::ptr<cq_bytes_in>(env, _in);

    std::vector<uint8_t> object = cq_cpp_bytes_from(in);
    cqJNIRef<jbyteArray> array = cqJNIType::jniDataAuto(env, object);

    env->CallStaticVoidMethod(JNI(), method, array.get());
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_JNI_makeIntListSuck
    (JNIEnv *env, jclass, jobject _in)
{
    static jmethodID method = nullptr;
    cqJNIEnv::staticMethod(&method, env, JNI(), "onIntListSuck", "(J)V");

    auto in = cqJNIType::ptr<cq_int_list_in>(env, _in);

    std::vector<int64_t> object = cq_cpp_int_list_from(in);
    for (auto &it : object) {
        env->CallStaticVoidMethod(JNI(), method, (jlong)it);
    }
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_JNI_makeStrListSuck
    (JNIEnv *env, jclass, jobject _in)
{
    static jmethodID method = nullptr;
    cqJNIEnv::staticMethod(&method, env, JNI(), "onStrListSuck", "(Ljava/lang/String;)V");

    auto in = cqJNIType::ptr<cq_str_list_in>(env, _in);

    std::vector<std::string> object = cq_cpp_str_list_from(in);
    for (auto &it : object) {
        cqJNIRef<jstring> string = cqJNIType::jniStringAuto(env, it.c_str());
        env->CallStaticVoidMethod(JNI(), method, string.get());
    }
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_JNI_makeSSMapSuck
    (JNIEnv *env, jclass, jobject _in)
{
    static jmethodID method = nullptr;
    cqJNIEnv::staticMethod(&method, env, JNI(), "onSSMapSuck", "(Ljava/lang/String;Ljava/lang/String;)V");

    auto in = cqJNIType::ptr<cq_ss_map_in>(env, _in);

    std::map<std::string, std::string> object = cq_cpp_ss_map_from(in);
    for (auto &cp : object) {
        cqJNIRef<jstring> key = cqJNIType::jniStringAuto(env, cp.first .c_str());
        cqJNIRef<jstring> val = cqJNIType::jniStringAuto(env, cp.second.c_str());
        env->CallStaticVoidMethod(JNI(), method, key.get(), val.get());
    }
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_JNI_makeBytesAssign
    (JNIEnv *env, jclass, jbyteArray _val, jobject _out)
{
    auto val = cqJNIType::data(env, _val);
    auto out = cqJNIType::ptr<cq_bytes_out>(env, _out);

    out(val.data(), (int32_t)val.size());
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_JNI_makeIntListAssign
    (JNIEnv *env, jclass, jlong value, jobject _out)
{
    auto out = cqJNIType::ptr<cq_int_list_out>(env, _out);

    out((int64_t)value);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_JNI_makeStrListAssign
    (JNIEnv *env, jclass, jstring _val, jobject _out)
{
    auto val = cqJNIType::string(env, _val);
    auto out = cqJNIType::ptr<cq_str_list_out>(env, _out);

    out(val.c_str());
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_JNI_makeSSMapAssign
    (JNIEnv *env, jclass, jstring _key, jstring _val, jobject _out)
{
    auto key = cqJNIType::string(env, _key);
    auto val = cqJNIType::string(env, _val);
    auto out = cqJNIType::ptr<cq_ss_map_out>(env, _out);

    out(key.c_str(), val.c_str());
}

//object reference:

static const int32_t JavaObjectMagic = 0x4A415641; //"JAVA".

static void release_raw_java(void *raw) {
    if (raw != nullptr) {
        cqJNIEnv::env()->DeleteGlobalRef((jobject)raw);
    }
}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_JNI_retainJavaObject
    (JNIEnv *env, jclass, jobject object, jstring cls)
{
    if (object == nullptr) {
        return nullptr;
    }

    void *raw = (void *)env->NewGlobalRef(object);
    cq_obj *ptr = cq_retain_raw_obj(raw, release_raw_java);

    std::string name = cqJNIType::string(env, cls);
    if (!name.empty()) {
        cq_set_obj_cls(ptr, name.c_str());
    }
    cq_set_obj_magic(ptr, JavaObjectMagic);

    return cqJNIType::jniPtr(env, ptr);
}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_JNI_makeObjectReturnRaw
    (JNIEnv *env, jclass, jobject _ptr)
{
    auto ptr = cqJNIType::ptr<cq_obj *>(env, _ptr);
    if (ptr == nullptr) {
        return nullptr;
    }

    if (cq_obj_magic(ptr) != JavaObjectMagic) {
        //it's not a java object.
        return nullptr;
    }

    jobject object = (jobject)cq_obj_raw(ptr);
    return env->NewLocalRef(object);
}
