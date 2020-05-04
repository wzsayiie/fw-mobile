#include "CBlock.hh"
#include "cqjnihelper.hh"

CQ_JNI_CLASS(CBlock, "src/library/basis/CBlock")

static void run_block(void *raw) {
    if (raw == nullptr) {
        return;
    }

    static jmethodID method = nullptr;

    JNIEnv *env = cqJNIEnv::env();
    cqJNIEnv::staticMethod(&method, env, CBlock(), __func__, "(Ljava/lang/Runnable;)V");

    env->CallStaticVoidMethod(CBlock(), method, (jobject)raw);
}

static void del_block(void *raw) {
    if (raw != nullptr) {
        cqJNIEnv::env()->DeleteGlobalRef((jobject)raw);
    }
}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CBlock_retainRaw
    (JNIEnv *env, jclass, jobject runnable)
{
    if (runnable != nullptr) {
        auto raw = (void *)env->NewGlobalRef(runnable);
        auto ptr = cq_block_retain_raw(raw, run_block, del_block);
        return cqJNIType::jniPtr(env, ptr);
    }
    return nullptr;
}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CBlock_retain
    (JNIEnv *env, jclass, jobject _j_block)
{
    auto block = cqJNIType::ptr<cq_block *>(env, _j_block);
    cq_block_retain(block);
    return _j_block;
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CBlock_release
    (JNIEnv *env, jclass, jobject _j_block)
{
    auto block = cqJNIType::ptr<cq_block *>(env, _j_block);
    cq_block_release(block);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CBlock_run
    (JNIEnv *env, jclass, jobject _j_block)
{
    auto block = cqJNIType::ptr<cq_block *>(env, _j_block);
    cq_block_run(block);
}
