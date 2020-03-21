#include "CFunc.hh"
#include "cqjnihelper.hh"

CQ_JNI_CLASS(CFunc, "src/library/basis/CFunc")

#define GEN_EVERY_OUT_FN(NAME, TYPE, J_NAME, J_SIGN)\
/**/    static void NAME(jobject dst, TYPE value) {\
/**/        static jmethodID method = nullptr;\
/**/        JNIEnv *env = cqJNIEnv::env();\
/**/        cqJNIEnv::staticMethod(&method, env, CFunc(), J_NAME, J_SIGN);\
/**/        env->CallStaticVoidMethod(CFunc(), method, dst, value);\
/**/    }

GEN_EVERY_OUT_FN(bool_out  , bool   , "onOutBool"  , "([Z,Z)V")
GEN_EVERY_OUT_FN(int8_out  , int8_t , "onOutInt8"  , "([B,B)V")
GEN_EVERY_OUT_FN(int16_out , int16_t, "onOutInt16" , "([S,S)V")
GEN_EVERY_OUT_FN(int32_out , int32_t, "onOutInt32" , "([I,I)V")
GEN_EVERY_OUT_FN(int64_out , int64_t, "onOutInt64" , "([J,J)V")
GEN_EVERY_OUT_FN(float_out , float  , "onOutFloat" , "([F,F)V")
GEN_EVERY_OUT_FN(double_out, double , "onOutDouble", "([D,D)V")

static void str_out(jobject dst, const char *_value) {
    static jmethodID method = nullptr;

    JNIEnv *env = cqJNIEnv::env();
    const char *func = "onOutStr";
    const char *sign = "(Ljava/lang/StringBuilder;Ljava/lang/String;)V";
    cqJNIEnv::staticMethod(&method, env, CFunc(), func, sign);

    jstring value = cqJNIType::jniString(env, _value);
    env->CallStaticVoidMethod(CFunc(), method, dst, value);
}

static void bytes_out(jobject dst, const void *bytes, int32_t len) {
    static jmethodID method = nullptr;

    JNIEnv *env = cqJNIEnv::env();
    const char *func = "onOutBytes";
    const char *sign = "(Ljava/nio/ByteBuffer;[Z)V";
    cqJNIEnv::staticMethod(&method, env, CFunc(), func, sign);

    jbyteArray value = cqJNIType::jniData(env, bytes, len);
    env->CallStaticVoidMethod(CFunc(), method, dst, value);
}

static void i64_list_out(jobject dst, int64_t item) {
    static jmethodID method = nullptr;

    JNIEnv *env = cqJNIEnv::env();
    const char *func = "onOutI64List";
    const char *sign = "(Ljava/util/ArrayList;J)V";
    cqJNIEnv::staticMethod(&method, env, CFunc(), func, sign);

    env->CallStaticVoidMethod(CFunc(), method, dst, item);
}

static void str_list_out(jobject dst, const char *_item) {
    static jmethodID method = nullptr;

    JNIEnv *env = cqJNIEnv::env();
    const char *func = "onOutStrList";
    const char *sign = "(Ljava/util/ArrayList;Ljava/lang/String;)V";
    cqJNIEnv::staticMethod(&method, env, CFunc(), func, sign);

    jstring item = cqJNIType::jniString(env, _item);
    env->CallStaticVoidMethod(CFunc(), method, dst, item);
}

static void ss_map_out(jobject dst, const char *_key, const char *_val) {
    static jmethodID method = nullptr;

    JNIEnv *env = cqJNIEnv::env();
    const char *func = "onOutSSMap";
    const char *sign = "(Ljava/util/HashMap;Ljava/lang/String;Ljava/lang/String;)V";
    cqJNIEnv::staticMethod(&method, env, CFunc(), func, sign);

    jstring key = cqJNIType::jniString(env, _key);
    jstring val = cqJNIType::jniString(env, _val);
    env->CallStaticVoidMethod(CFunc(), method, dst, key, val);
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

GEN_OUT_FN(bool_out  , (bool    v), v)
GEN_OUT_FN(int8_out  , (int8_t  v), v)
GEN_OUT_FN(int16_out , (int16_t v), v)
GEN_OUT_FN(int32_out , (int32_t v), v)
GEN_OUT_FN(int64_out , (int64_t v), v)
GEN_OUT_FN(float_out , (float   v), v)
GEN_OUT_FN(double_out, (double  v), v)

GEN_OUT_FN(str_out     , (const char *s               ), s   )
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

static cq_bool_out   cq_java_bool_out  (jbooleanArray dst) {RET_OUT_FN(bool_out  , dst)}
static cq_int8_out   cq_java_int8_out  (jbyteArray    dst) {RET_OUT_FN(int8_out  , dst)}
static cq_int16_out  cq_java_int16_out (jshortArray   dst) {RET_OUT_FN(int16_out , dst)}
static cq_int32_out  cq_java_int32_out (jintArray     dst) {RET_OUT_FN(int32_out , dst)}
static cq_int64_out  cq_java_int64_out (jlongArray    dst) {RET_OUT_FN(int64_out , dst)}
static cq_float_out  cq_java_float_out (jfloatArray   dst) {RET_OUT_FN(float_out , dst)}
static cq_double_out cq_java_double_out(jdoubleArray  dst) {RET_OUT_FN(double_out, dst)}

static cq_str_out      cq_java_str_out     (jobject dst) {RET_OUT_FN(str_out     , dst)}
static cq_bytes_out    cq_java_bytes_out   (jobject dst) {RET_OUT_FN(bytes_out   , dst)}
static cq_i64_list_out cq_java_i64_list_out(jobject dst) {RET_OUT_FN(i64_list_out, dst)}
static cq_str_list_out cq_java_str_list_out(jobject dst) {RET_OUT_FN(str_list_out, dst)}
static cq_ss_map_out   cq_java_ss_map_out  (jobject dst) {RET_OUT_FN(ss_map_out  , dst)}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_outBool  (JNIEnv *e, jclass, jbooleanArray d) {return cqJNIType::jniPtr(e, cq_java_bool_out  (d));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_outInt8  (JNIEnv *e, jclass, jbyteArray    d) {return cqJNIType::jniPtr(e, cq_java_int8_out  (d));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_outInt16 (JNIEnv *e, jclass, jshortArray   d) {return cqJNIType::jniPtr(e, cq_java_int16_out (d));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_outInt32 (JNIEnv *e, jclass, jintArray     d) {return cqJNIType::jniPtr(e, cq_java_int32_out (d));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_outInt64 (JNIEnv *e, jclass, jlongArray    d) {return cqJNIType::jniPtr(e, cq_java_int64_out (d));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_outFloat (JNIEnv *e, jclass, jfloatArray   d) {return cqJNIType::jniPtr(e, cq_java_float_out (d));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_outDouble(JNIEnv *e, jclass, jdoubleArray  d) {return cqJNIType::jniPtr(e, cq_java_double_out(d));}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_outStr    (JNIEnv *e, jclass, _jobject *d) {return cqJNIType::jniPtr(e, cq_java_str_out     (d));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_outBytes  (JNIEnv *e, jclass, _jobject *d) {return cqJNIType::jniPtr(e, cq_java_bytes_out   (d));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_outI64List(JNIEnv *e, jclass, _jobject *d) {return cqJNIType::jniPtr(e, cq_java_i64_list_out(d));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_outStrList(JNIEnv *e, jclass, _jobject *d) {return cqJNIType::jniPtr(e, cq_java_str_list_out(d));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_outSSMap  (JNIEnv *e, jclass, _jobject *d) {return cqJNIType::jniPtr(e, cq_java_ss_map_out  (d));}

static void bool_in  (intmax_t src, cq_bool_out   out) {if (out) out(*(bool    *)&src);}
static void int8_in  (intmax_t src, cq_int8_out   out) {if (out) out(*(int8_t  *)&src);}
static void int16_in (intmax_t src, cq_int16_out  out) {if (out) out(*(int16_t *)&src);}
static void int32_in (intmax_t src, cq_int32_out  out) {if (out) out(*(int32_t *)&src);}
static void int64_in (intmax_t src, cq_int64_out  out) {if (out) out(/*int64_t */ src);}
static void float_in (intmax_t src, cq_float_out  out) {if (out) out(*(float   *)&src);}
static void double_in(intmax_t src, cq_double_out out) {if (out) out(*(double  *)&src);}

static void str_in(intmax_t _src, cq_str_out out) {
    if (_src == 0 || out == nullptr) {
        return;
    }

    JNIEnv *env = cqJNIEnv::env();
    std::string src = cqJNIType::string(env, *(jstring *)&_src);
    out(src.c_str());
}

static void bytes_in(intmax_t _src, cq_bytes_out out) {
    if (_src == 0 || out == nullptr) {
        return;
    }

    JNIEnv *env = cqJNIEnv::env();
    std::vector<uint8_t> src = cqJNIType::data(env, *(jbyteArray *)&_src);
    out(src.data(), (int32_t)src.size());
}

#define GEN_EVERY_IN_FN(NAME, TYPE, J_NAME, J_SIGN)\
/**/    static void NAME(intmax_t _src, TYPE _out) {\
/**/        if (_src == 0 || _out == nullptr) {\
/**/            return;\
/**/        }\
/**/        \
/**/        static jmethodID method = nullptr;\
/**/        JNIEnv *env = cqJNIEnv::env();\
/**/        cqJNIEnv::staticMethod(&method, env, CFunc(), J_NAME, J_SIGN);\
/**/        \
/**/        jobject src = *(jobject *)&_src;\
/**/        jobject out = cqJNIType::jniPtr(env, _out);\
/**/        env->CallStaticVoidMethod(CFunc(), method, src, out);\
/**/    }

GEN_EVERY_IN_FN(i64_list_in, cq_i64_list_out, "onInI64List", "(Ljava/util/ArrayList;" "Lsrc/library/basis/CPtr;)V")
GEN_EVERY_IN_FN(str_list_in, cq_str_list_out, "onInStrList", "(Ljava/util/ArrayList;" "Lsrc/library/basis/CPtr;)V")
GEN_EVERY_IN_FN(ss_map_in  , cq_ss_map_out  , "onInSSMap"  , "(Ljava/util/HashMap;"   "Lsrc/library/basis/CPtr;)V")

#define GEN_IN_FN(FN, PARAM, ...)\
/**/    static thread_local intmax_t FN##_src_0 = 0;\
/**/    static thread_local intmax_t FN##_src_1 = 0;\
/**/    static thread_local intmax_t FN##_src_2 = 0;\
/**/    static thread_local intmax_t FN##_src_3 = 0;\
/**/    static void FN##_0 PARAM {FN(FN##_src_0, __VA_ARGS__);}\
/**/    static void FN##_1 PARAM {FN(FN##_src_1, __VA_ARGS__);}\
/**/    static void FN##_2 PARAM {FN(FN##_src_2, __VA_ARGS__);}\
/**/    static void FN##_3 PARAM {FN(FN##_src_3, __VA_ARGS__);}

GEN_IN_FN(bool_in  , (cq_bool_out   out), out)
GEN_IN_FN(int8_in  , (cq_int8_out   out), out)
GEN_IN_FN(int16_in , (cq_int16_out  out), out)
GEN_IN_FN(int32_in , (cq_int32_out  out), out)
GEN_IN_FN(int64_in , (cq_int64_out  out), out)
GEN_IN_FN(float_in , (cq_float_out  out), out)
GEN_IN_FN(double_in, (cq_double_out out), out)

GEN_IN_FN(str_in     , (cq_str_out      out), out)
GEN_IN_FN(bytes_in   , (cq_bytes_out    out), out)
GEN_IN_FN(i64_list_in, (cq_i64_list_out out), out)
GEN_IN_FN(str_list_in, (cq_str_list_out out), out)
GEN_IN_FN(ss_map_in  , (cq_ss_map_out   out), out)

#define RET_IN_FN(FN, VALUE)\
/**/    static thread_local int32_t n = 0;\
/**/    n = (n + 1) % 4;\
/**/    switch (n) {\
/**/        case  0: FN##_src_0 = *(intmax_t *)&VALUE; return FN##_0;\
/**/        case  1: FN##_src_1 = *(intmax_t *)&VALUE; return FN##_1;\
/**/        case  2: FN##_src_2 = *(intmax_t *)&VALUE; return FN##_2;\
/**/        default: FN##_src_3 = *(intmax_t *)&VALUE; return FN##_3;\
/**/    }

static cq_bool_in   cq_java_bool_in  (jboolean   src) {RET_IN_FN(bool_in  , src)}
static cq_int8_in   cq_java_int8_in  (jbyte      src) {RET_IN_FN(int8_in  , src)}
static cq_int16_in  cq_java_int16_in (jshort     src) {RET_IN_FN(int16_in , src)}
static cq_int32_in  cq_java_int32_in (jint       src) {RET_IN_FN(int32_in , src)}
static cq_int64_in  cq_java_int64_in (jlong      src) {RET_IN_FN(int64_in , src)}
static cq_float_in  cq_java_float_in (jfloat     src) {RET_IN_FN(float_in , src)}
static cq_double_in cq_java_double_in(jdouble    src) {RET_IN_FN(double_in, src)}
static cq_str_in    cq_java_str_in   (jstring    src) {RET_IN_FN(str_in   , src)}
static cq_bytes_in  cq_java_bytes_in (jbyteArray src) {RET_IN_FN(bytes_in , src)}

static cq_i64_list_in cq_java_i64_list_in(jobject src) {RET_IN_FN(i64_list_in, src)}
static cq_str_list_in cq_java_str_list_in(jobject src) {RET_IN_FN(str_list_in, src)}
static cq_ss_map_in   cq_java_ss_map_in  (jobject src) {RET_IN_FN(ss_map_in  , src)}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_inBool  (JNIEnv *e, jclass, jboolean   v) {return cqJNIType::jniPtr(e, cq_java_bool_in  (v));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_inInt8  (JNIEnv *e, jclass, jbyte      v) {return cqJNIType::jniPtr(e, cq_java_int8_in  (v));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_inInt16 (JNIEnv *e, jclass, jshort     v) {return cqJNIType::jniPtr(e, cq_java_int16_in (v));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_inInt32 (JNIEnv *e, jclass, jint       v) {return cqJNIType::jniPtr(e, cq_java_int32_in (v));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_inInt64 (JNIEnv *e, jclass, jlong      v) {return cqJNIType::jniPtr(e, cq_java_int64_in (v));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_inFloat (JNIEnv *e, jclass, jfloat     v) {return cqJNIType::jniPtr(e, cq_java_float_in (v));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_inDouble(JNIEnv *e, jclass, jdouble    v) {return cqJNIType::jniPtr(e, cq_java_double_in(v));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_inStr   (JNIEnv *e, jclass, jstring    v) {return cqJNIType::jniPtr(e, cq_java_str_in   (v));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_inBytes (JNIEnv *e, jclass, jbyteArray v) {return cqJNIType::jniPtr(e, cq_java_bytes_in (v));}

extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_inI64List(JNIEnv *e, jclass, _jobject *v) {return cqJNIType::jniPtr(e, cq_java_i64_list_in(v));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_inStrList(JNIEnv *e, jclass, _jobject *v) {return cqJNIType::jniPtr(e, cq_java_str_list_in(v));}
extern "C" JNIEXPORT jobject JNICALL Java_src_library_basis_CFunc_inSSMap  (JNIEnv *e, jclass, _jobject *v) {return cqJNIType::jniPtr(e, cq_java_ss_map_in  (v));}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CFunc_appendI64List
    (JNIEnv *env, jclass, jlong val, jobject _out)
{
    if (_out != nullptr) {
        auto out = cqJNIType::ptr<cq_i64_list_out>(env, _out);
        out(val);
    }
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CFunc_appendStrList
    (JNIEnv *env, jclass, jstring _val, jobject _out)
{
    if (_val && _out) {
        auto val = cqJNIType::string(env, _val);
        auto out = cqJNIType::ptr<cq_str_list_out>(env, _out);
        out(val.c_str());
    }
}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CFunc_appendSSMap
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

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CFunc_assignBool  (JNIEnv *e, jclass, jobject in, jobject out) {ASSIGN(e, cq_bool_in  , in, cq_bool_out  , out)}
extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CFunc_assignInt8  (JNIEnv *e, jclass, jobject in, jobject out) {ASSIGN(e, cq_int8_in  , in, cq_int8_out  , out)}
extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CFunc_assignInt16 (JNIEnv *e, jclass, jobject in, jobject out) {ASSIGN(e, cq_int16_in , in, cq_int16_out , out)}
extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CFunc_assignInt32 (JNIEnv *e, jclass, jobject in, jobject out) {ASSIGN(e, cq_int32_in , in, cq_int32_out , out)}
extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CFunc_assignInt64 (JNIEnv *e, jclass, jobject in, jobject out) {ASSIGN(e, cq_int64_in , in, cq_int64_out , out)}
extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CFunc_assignFloat (JNIEnv *e, jclass, jobject in, jobject out) {ASSIGN(e, cq_float_in , in, cq_float_out , out)}
extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CFunc_assignDouble(JNIEnv *e, jclass, jobject in, jobject out) {ASSIGN(e, cq_double_in, in, cq_double_out, out)}
extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CFunc_assignStr   (JNIEnv *e, jclass, jobject in, jobject out) {ASSIGN(e, cq_str_in   , in, cq_str_out   , out)}
extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CFunc_assignBytes (JNIEnv *e, jclass, jobject in, jobject out) {ASSIGN(e, cq_bytes_in , in, cq_bytes_out , out)}

extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CFunc_assignI64List(JNIEnv *e, jclass, jobject in, jobject out) {ASSIGN(e, cq_i64_list_in, in, cq_i64_list_out, out)}
extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CFunc_assignStrList(JNIEnv *e, jclass, jobject in, jobject out) {ASSIGN(e, cq_str_list_in, in, cq_str_list_out, out)}
extern "C" JNIEXPORT void JNICALL Java_src_library_basis_CFunc_assignSSMap  (JNIEnv *e, jclass, jobject in, jobject out) {ASSIGN(e, cq_ss_map_in  , in, cq_ss_map_out  , out)}
