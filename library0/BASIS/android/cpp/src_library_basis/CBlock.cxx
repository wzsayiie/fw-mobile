#include "CBlock.hh"
#include "cqjnihelper.hh"

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CBlock_run
    (JNIEnv *env, jclass, jobject _block, jobject _data)
{
    auto block = cqJNIType::ptr<cq_block>(env, _block);
    auto data  = cqJNIType::ptr<void *  >(env, _data );

    cq_run_block(block, data);
}
