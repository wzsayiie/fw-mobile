#include "CParam.hh"
#include "cqjnihelper.hh"

CQ_JNI_CLASS(CParam, "src/library/basis/CParam")

static void bytes_out(jobject dst, const void *bytes, int32_t len) {
    static jmethodID method = nullptr;

    JNIEnv *env = cqJNIEnv::env();
    const char *func = "onOutBytes";
    const char *sign = "(Ljava/nio/ByteBuffer;[Z)V";
    cqJNIEnv::staticMethod(&method, env, CParam(), func, sign);

    jbyteArray value = cqJNIType::jniData(env, bytes, len);
    env->CallStaticVoidMethod(CParam(), method, dst, value);
}

static void i64_list_out(jobject dst, int64_t item) {
    static jmethodID method = nullptr;

    JNIEnv *env = cqJNIEnv::env();
    const char *func = "onOutI64List";
    const char *sign = "(Ljava/util/ArrayList;J)V";
    cqJNIEnv::staticMethod(&method, env, CParam(), func, sign);

    env->CallStaticVoidMethod(CParam(), method, dst, item);
}

static void str_list_out(jobject dst, const char *_item) {
    static jmethodID method = nullptr;

    JNIEnv *env = cqJNIEnv::env();
    const char *func = "onOutStrList";
    const char *sign = "(Ljava/util/ArrayList;Ljava/lang/String;)V";
    cqJNIEnv::staticMethod(&method, env, CParam(), func, sign);

    jstring item = cqJNIType::jniString(env, _item);
    env->CallStaticVoidMethod(CParam(), method, dst, item);
}

static void ss_map_out(jobject dst, const char *_key, const char *_val) {
    static jmethodID method = nullptr;

    JNIEnv *env = cqJNIEnv::env();
    const char *func = "onOutSSMap";
    const char *sign = "(Ljava/util/HashMap;Ljava/lang/String;Ljava/lang/String;)V";
    cqJNIEnv::staticMethod(&method, env, CParam(), func, sign);

    jstring key = cqJNIType::jniString(env, _key);
    jstring val = cqJNIType::jniString(env, _val);
    env->CallStaticVoidMethod(CParam(), method, dst, key, val);
}

#define GEN_OUT_FN(FN, PARAM, ...)\
/**/    static thread_local jobject FN##_dst_0 = NULL;\
/**/    static thread_local jobject FN##_dst_1 = NULL;\
/**/    static thread_local jobject FN##_dst_2 = NULL;\
/**/    static thread_local jobject FN##_dst_3 = NULL;\
/**/    static void FN##_0 PARAM {FN(FN##_dst_0, __VA_ARGS__);}\
/**/    static void FN##_1 PARAM {FN(FN##_dst_1, __VA_ARGS__);}\
/**/    static void FN##_2 PARAM {FN(FN##_dst_2, __VA_ARGS__);}\
/**/    static void FN##_3 PARAM {FN(FN##_dst_3, __VA_ARGS__);}

GEN_OUT_FN(bytes_out   , (const void *p, int32_t     n), p, n)
GEN_OUT_FN(i64_list_out, (int64_t     i               ), i   )
GEN_OUT_FN(str_list_out, (const char *i               ), i   )
GEN_OUT_FN(ss_map_out  , (const char *k, const char *v), k, v)

#define RET_OUT_FN(FN, VALUE)\
/**/    static thread_local int32_t n = 0;\
/**/    n = (n + 1) % 4;\
/**/    switch (n) {\
/**/        case  0: FN##_dst_0 = VALUE; return FN##_0;\
/**/        case  1: FN##_dst_1 = VALUE; return FN##_1;\
/**/        case  2: FN##_dst_2 = VALUE; return FN##_2;\
/**/        default: FN##_dst_3 = VALUE; return FN##_3;\
/**/    }

static cq_bytes_out    cq_java_bytes_out   (jobject dst) {RET_OUT_FN(bytes_out   , dst)}
static cq_i64_list_out cq_java_i64_list_out(jobject dst) {RET_OUT_FN(i64_list_out, dst)}
static cq_str_list_out cq_java_str_list_out(jobject dst) {RET_OUT_FN(str_list_out, dst)}
static cq_ss_map_out   cq_java_ss_map_out  (jobject dst) {RET_OUT_FN(ss_map_out  , dst)}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CParam_outBytes  (JNIEnv *e, jclass, _jobject *d) {return cqJNIType::jniPtr(e, cq_java_bytes_out   (d));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CParam_outI64List(JNIEnv *e, jclass, _jobject *d) {return cqJNIType::jniPtr(e, cq_java_i64_list_out(d));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CParam_outStrList(JNIEnv *e, jclass, _jobject *d) {return cqJNIType::jniPtr(e, cq_java_str_list_out(d));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CParam_outSSMap  (JNIEnv *e, jclass, _jobject *d) {return cqJNIType::jniPtr(e, cq_java_ss_map_out  (d));}

static void bytes_in(jobject _src, cq_bytes_out out) {
    if (_src == nullptr || out == nullptr) {
        return;
    }

    JNIEnv *env = cqJNIEnv::env();
    std::vector<uint8_t> src = cqJNIType::data(env, (jbyteArray)_src);
    out(src.data(), (int32_t)src.size());
}

#define GEN_EVERY_IN_FN(NAME, TYPE, J_NAME, J_SIGN)\
/**/    static void NAME(jobject src, TYPE _out) {\
/**/        if (src == nullptr || _out == nullptr) {\
/**/            return;\
/**/        }\
/**/        \
/**/        static jmethodID method = nullptr;\
/**/        JNIEnv *env = cqJNIEnv::env();\
/**/        cqJNIEnv::staticMethod(&method, env, CParam(), J_NAME, J_SIGN);\
/**/        \
/**/        jobject out = cqJNIType::jniPtr(env, _out);\
/**/        env->CallStaticVoidMethod(CParam(), method, src, out);\
/**/    }

GEN_EVERY_IN_FN(i64_list_in, cq_i64_list_out, "onInI64List", "(Ljava/util/ArrayList;" "Lsrc/library/basis/CPtr;)V")
GEN_EVERY_IN_FN(str_list_in, cq_str_list_out, "onInStrList", "(Ljava/util/ArrayList;" "Lsrc/library/basis/CPtr;)V")
GEN_EVERY_IN_FN(ss_map_in  , cq_ss_map_out  , "onInSSMap"  , "(Ljava/util/HashMap;"   "Lsrc/library/basis/CPtr;)V")

#define GEN_IN_FN(FN, PARAM, ...)\
/**/    static thread_local jobject FN##_src_0 = 0;\
/**/    static thread_local jobject FN##_src_1 = 0;\
/**/    static thread_local jobject FN##_src_2 = 0;\
/**/    static thread_local jobject FN##_src_3 = 0;\
/**/    static void FN##_0 PARAM {FN(FN##_src_0, __VA_ARGS__);}\
/**/    static void FN##_1 PARAM {FN(FN##_src_1, __VA_ARGS__);}\
/**/    static void FN##_2 PARAM {FN(FN##_src_2, __VA_ARGS__);}\
/**/    static void FN##_3 PARAM {FN(FN##_src_3, __VA_ARGS__);}

GEN_IN_FN(bytes_in   , (cq_bytes_out    out), out)
GEN_IN_FN(i64_list_in, (cq_i64_list_out out), out)
GEN_IN_FN(str_list_in, (cq_str_list_out out), out)
GEN_IN_FN(ss_map_in  , (cq_ss_map_out   out), out)

#define RET_IN_FN(FN, VALUE)\
/**/    static thread_local int32_t n = 0;\
/**/    n = (n + 1) % 4;\
/**/    switch (n) {\
/**/        case  0: FN##_src_0 = VALUE; return FN##_0;\
/**/        case  1: FN##_src_1 = VALUE; return FN##_1;\
/**/        case  2: FN##_src_2 = VALUE; return FN##_2;\
/**/        default: FN##_src_3 = VALUE; return FN##_3;\
/**/    }

static cq_bytes_in    cq_java_bytes_in   (jobject src) {RET_IN_FN(bytes_in   , src)}
static cq_i64_list_in cq_java_i64_list_in(jobject src) {RET_IN_FN(i64_list_in, src)}
static cq_str_list_in cq_java_str_list_in(jobject src) {RET_IN_FN(str_list_in, src)}
static cq_ss_map_in   cq_java_ss_map_in  (jobject src) {RET_IN_FN(ss_map_in  , src)}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CParam_inBytes  (JNIEnv *e, jclass, jbyteArray v) {return cqJNIType::jniPtr(e, cq_java_bytes_in   (v));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CParam_inI64List(JNIEnv *e, jclass, _jobject  *v) {return cqJNIType::jniPtr(e, cq_java_i64_list_in(v));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CParam_inStrList(JNIEnv *e, jclass, _jobject  *v) {return cqJNIType::jniPtr(e, cq_java_str_list_in(v));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CParam_inSSMap  (JNIEnv *e, jclass, _jobject  *v) {return cqJNIType::jniPtr(e, cq_java_ss_map_in  (v));}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CParam_appendI64List
    (JNIEnv *env, jclass, jlong val, jobject _out)
{
    if (_out != nullptr) {
        auto out = cqJNIType::ptr<cq_i64_list_out>(env, _out);
        out(val);
    }
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CParam_appendStrList
    (JNIEnv *env, jclass, jstring _val, jobject _out)
{
    if (_val && _out) {
        auto val = cqJNIType::string(env, _val);
        auto out = cqJNIType::ptr<cq_str_list_out>(env, _out);
        out(val.c_str());
    }
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CParam_appendSSMap
    (JNIEnv *env, jclass, jstring _key, jstring _val, jobject _out)
{
    if (_key && _val && _out) {
        auto key = cqJNIType::string(env, _key);
        auto val = cqJNIType::string(env, _val);
        auto out = cqJNIType::ptr<cq_ss_map_out>(env, _out);
        out(key.c_str(), val.c_str());
    }
}

#define ASSIGN(ENV, IN_T, IN, OUT_T, OUT)\
/**/    if (IN && OUT) {\
/**/        auto __in  = cqJNIType::ptr<IN_T >(ENV, IN );\
/**/        auto __out = cqJNIType::ptr<OUT_T>(ENV, OUT);\
/**/        __in(__out);\
/**/    }

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CParam_assignBytes  (JNIEnv *e, jclass, jobject in, jobject out) {ASSIGN(e, cq_bytes_in   , in, cq_bytes_out   , out)}
extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CParam_assignI64List(JNIEnv *e, jclass, jobject in, jobject out) {ASSIGN(e, cq_i64_list_in, in, cq_i64_list_out, out)}
extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CParam_assignStrList(JNIEnv *e, jclass, jobject in, jobject out) {ASSIGN(e, cq_str_list_in, in, cq_str_list_out, out)}
extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CParam_assignSSMap  (JNIEnv *e, jclass, jobject in, jobject out) {ASSIGN(e, cq_ss_map_in  , in, cq_ss_map_out  , out)}
