#include "CStruct.hh"
#include "cqjnihelper.hh"

CQ_JNI_CLASS(CStruct, "src/library/basis/CStruct");

inline int32_t j_int(void *value) {
    auto ptr = (intptr_t)value;
    return (int32_t)ptr;
}
inline void *j_vp(int32_t value) {
    intptr_t ptr = value;
    return (void *)ptr;
}

//clear methods:

static void bytes_clear     (void *d) { CQ_JNI_STATIC_METHOD(CStruct, m, __func__); m.fn<void>(j_int(d)); }
static void int64_list_clear(void *d) { CQ_JNI_STATIC_METHOD(CStruct, m, __func__); m.fn<void>(j_int(d)); }
static void str_list_clear  (void *d) { CQ_JNI_STATIC_METHOD(CStruct, m, __func__); m.fn<void>(j_int(d)); }
static void ss_map_clear    (void *d) { CQ_JNI_STATIC_METHOD(CStruct, m, __func__); m.fn<void>(j_int(d)); }

//receive methods:

static void bytes_recv(void *dst, const void *bytes, int32_t length) {
    static jmethodID method = nullptr;

    JNIEnv *env = cqJNIEnv::env();
    jbyteArray data = cqJNIType::jniData(env, bytes, length);

    cqJNIEnv::staticMethod(&method, env, CStruct(), __func__, "(I[B)V");
    env->CallStaticVoidMethod(CStruct(), method, j_int(dst), data);
}

static void int64_list_recv(void *dst, int64_t item) {
    CQ_JNI_STATIC_METHOD(CStruct, method, __func__);
    method.fn<void>(j_int(dst), item);
}

static void str_list_recv(void *dst, const char *item) {
    CQ_JNI_STATIC_METHOD(CStruct, method, __func__);
    method.fn<void>(j_int(dst), item);
}

static void ss_map_recv(void *dst, const char *key, const char *value) {
    CQ_JNI_STATIC_METHOD(CStruct, method, __func__);
    method.fn<void>(j_int(dst), key, value);
}

//send methods:

static void bytes_send(void *src, cq_bytes *dst) {
    CQ_JNI_STATIC_METHOD(CStruct, method, __func__);
    method.fn<void>(j_int(src), dst);
}

static void int64_list_send(void *src, cq_int64_list *dst) {
    CQ_JNI_STATIC_METHOD(CStruct, method, __func__);
    method.fn<void>(j_int(src), dst);
}

static void str_list_send(void *src, cq_str_list *dst) {
    CQ_JNI_STATIC_METHOD(CStruct, method, __func__);
    method.fn<void>(j_int(src), dst);
}

static void ss_map_send(void *src, cq_ss_map *dst) {
    CQ_JNI_STATIC_METHOD(CStruct, method, __func__);
    method.fn<void>(j_int(src), dst);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CStruct_sendBytes
    (JNIEnv *env, jclass, jbyteArray _j_data, jobject _j_dst)
{
    auto data = cqJNIType::data(env, _j_data);
    auto dst  = cqJNIType::ptr<cq_bytes *>(env, _j_dst);

    dst->recv(dst->ref, data.data(), (int32_t)data.size());
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CStruct_sendInt64List
    (JNIEnv *env, jclass, jlong item, jobject _j_dst)
{
    auto dst = cqJNIType::ptr<cq_int64_list *>(env, _j_dst);

    dst->recv(dst->ref, (int64_t)item);
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CStruct_sendStrList
    (JNIEnv *env, jclass, jstring _j_item, jobject _j_dst)
{
    auto item = cqJNIType::string(env, _j_item);
    auto dst  = cqJNIType::ptr<cq_str_list *>(env, _j_dst);

    dst->recv(dst->ref, item.c_str());
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CStruct_sendSSMap
    (JNIEnv *env, jclass, jstring _j_key, jstring _j_value, jobject _j_dst)
{
    auto key   = cqJNIType::string(env, _j_key);
    auto value = cqJNIType::string(env, _j_value);
    auto dst   = cqJNIType::ptr<cq_ss_map *>(env, _j_dst);

    dst->recv(dst->ref, key.c_str(), value.c_str());
}

//make a c ref to a java object:

const int BYTES      = 1;
const int INT64_LIST = 2;
const int STR_LIST   = 3;
const int SS_MAP     = 4;

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CStruct_generateStruct
    (JNIEnv *env, jclass, jint index, jint type)
{
    if (type == BYTES) {

        auto ptr = (cq_bytes *)auto_alloc(sizeof(cq_bytes));
        ptr->clear = bytes_clear;
        ptr->recv  = bytes_recv;
        ptr->send  = bytes_send;
        ptr->ref   = j_vp(index);
        return cqJNIType::jniPtr(env, ptr);

    } else if (type == INT64_LIST) {

        auto ptr = (cq_int64_list *)auto_alloc(sizeof(cq_int64_list));
        ptr->clear = int64_list_clear;
        ptr->recv  = int64_list_recv;
        ptr->send  = int64_list_send;
        ptr->ref   = j_vp(index);
        return cqJNIType::jniPtr(env, ptr);

    } else if (type == STR_LIST) {

        auto ptr = (cq_str_list *)auto_alloc(sizeof(cq_str_list));
        ptr->clear = str_list_clear;
        ptr->recv  = str_list_recv;
        ptr->send  = str_list_send;
        ptr->ref   = j_vp(index);
        return cqJNIType::jniPtr(env, ptr);

    } else if (type == SS_MAP) {

        auto ptr = (cq_ss_map *)auto_alloc(sizeof(cq_ss_map));
        ptr->clear = ss_map_clear;
        ptr->recv  = ss_map_recv;
        ptr->send  = ss_map_send;
        ptr->ref   = j_vp(index);
        return cqJNIType::jniPtr(env, ptr);

    }

    return nullptr;
}

//methods for c types:

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CStruct_clear
    (JNIEnv *env, jclass, jobject _j_dst, jint type)
{
    auto dst = cqJNIType::ptr<void *>(env, _j_dst);

    switch (type) {
        case BYTES     : cq_bytes_clear     ((cq_bytes      *)dst); break;
        case INT64_LIST: cq_int64_list_clear((cq_int64_list *)dst); break;
        case STR_LIST  : cq_str_list_clear  ((cq_str_list   *)dst); break;
        case SS_MAP    : cq_ss_map_clear    ((cq_ss_map     *)dst); break;
        default:;
    }
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CStruct_append
    (JNIEnv *env, jclass, jobject _j_d, jobject _j_s, jint type)
{
    auto d = cqJNIType::ptr<void *>(env, _j_d);
    auto s = cqJNIType::ptr<void *>(env, _j_s);

    switch (type) {
        case BYTES     : cq_bytes_append     ((cq_bytes      *)d, (cq_bytes      *)s); break;
        case INT64_LIST: cq_int64_list_append((cq_int64_list *)d, (cq_int64_list *)s); break;
        case STR_LIST  : cq_str_list_append  ((cq_str_list   *)d, (cq_str_list   *)s); break;
        case SS_MAP    : cq_ss_map_append    ((cq_ss_map     *)d, (cq_ss_map     *)s); break;
        default:;
    }
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CStruct_assign
    (JNIEnv *env, jclass, jobject _j_d, jobject _j_s, jint type)
{
    auto d = cqJNIType::ptr<void *>(env, _j_d);
    auto s = cqJNIType::ptr<void *>(env, _j_s);

    switch (type) {
        case BYTES     : cq_bytes_assign     ((cq_bytes      *)d, (cq_bytes      *)s); break;
        case INT64_LIST: cq_int64_list_assign((cq_int64_list *)d, (cq_int64_list *)s); break;
        case STR_LIST  : cq_str_list_assign  ((cq_str_list   *)d, (cq_str_list   *)s); break;
        case SS_MAP    : cq_ss_map_assign    ((cq_ss_map     *)d, (cq_ss_map     *)s); break;
        default:;
    }
}
