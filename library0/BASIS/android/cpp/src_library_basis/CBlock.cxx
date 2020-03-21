#include "CBlock.hh"
#include "cqjnihelper.hh"

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CBlock_run
    (JNIEnv *env, jclass, jobject _block, jobject _data)
{
    auto block = cqJNIType::ptr<cq_block>(env, _block);
    auto data  = cqJNIType::ptr<void *  >(env, _data );

    cq_run_block(block, data);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CBlock_setParam
    (JNIEnv *env, jclass, jstring _name, jint type, jobject _ptr)
{
    std::string name = cqJNIType::string(env, _name);
    void *ptr = cqJNIType::voidPtr(env, _ptr);

    cq_set_block_param(name.c_str(), type, ptr);
}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CBlock_param
    (JNIEnv *env, jclass, jstring _name, jint type)
{
    std::string name = cqJNIType::string(env, _name);
    void *ptr = cq_block_param(name.c_str(), type);
    return cqJNIType::jniPtr(env, ptr);
}
