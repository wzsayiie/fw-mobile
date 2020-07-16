#include "CRef.hh"
#include "cqjnihelper.hh"

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CRef_retain
    (JNIEnv *env, jclass, jobject _j_ref)
{
    auto ref = cqJNIType::ptr<cq_ref *>(env, _j_ref);
    cq_retain(ref);
    return _j_ref;
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CRef_release
    (JNIEnv *env, jclass, jobject _j_ref)
{
    auto ref = cqJNIType::ptr<cq_ref *>(env, _j_ref);
    cq_release(ref);
}
