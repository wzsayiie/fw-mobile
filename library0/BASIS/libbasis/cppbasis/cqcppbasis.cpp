#include "cqcppbasis.hh"

//std extension:

std::string cqString::make(const char *value) {
    return value ? value : "";
}

bool cqString::empty(const char *value) {
    return value == nullptr || *value == '\0';
}

//synchronization lock:

const int32_t MUTEX_NUMBER = 32;

std::mutex *cqMutex::random(const void *hash) {
    static std::mutex *list = nullptr;
    cq_synchronize({
        if (list == nullptr) {
            list = new std::mutex[MUTEX_NUMBER];
        }
    });
    
    int32_t local = (uintptr_t)hash % MUTEX_NUMBER;
    return list + local;
}

//class:

void _cqBaseObject::init() {
}

cqClass *_cqBaseObject::superclass       () { return nullptr; }
cqClass *_cqBaseObject::clazz            () { return nullptr; }
cqClass *_cqBaseObject::dynamicSuperclass() { return nullptr; }
cqClass *_cqBaseObject::dynamicClass     () { return nullptr; }

_cqBaseObject::~_cqBaseObject() {
}

bool cqClass::isKindOfClass(cqClass *cls) const {
    if (cls == nullptr) {
        return false;
    }
    
    if (this == cls) {
        return true;
    }
    for (auto it = superclass; it; it = it->superclass) {
        if (it == cls) {
            return true;
        }
    }
    return false;
}

//object:

cq_member(cqObject) {
};

bool cqObject::isKindOfClass(cqClass *cls) {
    return dynamicClass()->isKindOfClass(cls);
}

bool cqObject::isMemberOfClass(cqClass *cls) {
    if (cls == nullptr) {
        return false;
    }
    return dynamicClass() == cls;
}

//proxy:

cq_member(cqProxy) {
    cqObjectWeakRef core;
};

void cqProxy::init() {
    init(nullptr);
}

void cqProxy::init(cqObjectRef core) {
    super::init();
    
    setCore(core);
}

void cqProxy::setCore(cqObjectRef core) {
    dat->core = core;
}

cqObjectRef cqProxy::core() {
    return dat->core.lock();
}

_CQBASIS_BEGIN_VERSION_NS

//data interfaces for interaction with c:

static void bool_out  (void *dst, bool    value) {if (dst) *(bool    *)dst = value;}
static void int8_out  (void *dst, int8_t  value) {if (dst) *(int8_t  *)dst = value;}
static void int16_out (void *dst, int16_t value) {if (dst) *(int16_t *)dst = value;}
static void int32_out (void *dst, int32_t value) {if (dst) *(int32_t *)dst = value;}
static void int64_out (void *dst, int64_t value) {if (dst) *(int64_t *)dst = value;}
static void float_out (void *dst, float   value) {if (dst) *(float   *)dst = value;}
static void double_out(void *dst, double  value) {if (dst) *(double  *)dst = value;}

static void str_out(void *dst, const char *str) {
    if (dst == NULL) {
        return;
    }
    auto object = (std::string *)dst;
    object->assign(cqString::make(str));
}

static void bytes_out(void *dst, const void *ptr, int32_t len) {
    if (dst == NULL) {
        return;
    }
    auto object = (std::vector<uint8_t> *)dst;
    if (ptr && len > 0) {
        object->assign((uint8_t *)ptr, (uint8_t *)ptr + len);
    }
}

static void i64_list_out(void *dst, int64_t value) {
    if (dst == NULL) {
        return;
    }
    auto object = (std::vector<int64_t> *)dst;
    object->push_back(value);
}

static void str_list_out(void *dst, const char *value) {
    if (dst == NULL) {
        return;
    }
    auto object = (std::vector<std::string> *)dst;
    object->push_back(cqString::make(value));
}

static void ss_map_out(void *dst, const char *key, const char *value) {
    if (dst == NULL) {
        return;
    }
    auto object = (std::map<std::string, std::string> *)dst;
    if (!cq_str_empty(key)) {
        (*object)[key] = cqString::make(value);
    }
}

#define GEN_OUT_FN(FN, PARAM, ...)\
/**/    static thread_local void *FN##_dst_0 = NULL;\
/**/    static thread_local void *FN##_dst_1 = NULL;\
/**/    static thread_local void *FN##_dst_2 = NULL;\
/**/    static thread_local void *FN##_dst_3 = NULL;\
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

cq_bool_out   cq_cpp_out(bool    &value) {RET_OUT_FN(bool_out  , &value);}
cq_int8_out   cq_cpp_out(int8_t  &value) {RET_OUT_FN(int8_out  , &value);}
cq_int16_out  cq_cpp_out(int16_t &value) {RET_OUT_FN(int16_out , &value);}
cq_int32_out  cq_cpp_out(int32_t &value) {RET_OUT_FN(int32_out , &value);}
cq_int64_out  cq_cpp_out(int64_t &value) {RET_OUT_FN(int64_out , &value);}
cq_float_out  cq_cpp_out(float   &value) {RET_OUT_FN(float_out , &value);}
cq_double_out cq_cpp_out(double  &value) {RET_OUT_FN(double_out, &value);}

cq_str_out      cq_cpp_out(std::string                        &v) {RET_OUT_FN(str_out     , &v);}
cq_bytes_out    cq_cpp_out(std::vector<uint8_t>               &v) {RET_OUT_FN(bytes_out   , &v);}
cq_i64_list_out cq_cpp_out(std::vector<int64_t>               &v) {RET_OUT_FN(i64_list_out, &v);}
cq_str_list_out cq_cpp_out(std::vector<std::string>           &v) {RET_OUT_FN(str_list_out, &v);}
cq_ss_map_out   cq_cpp_out(std::map<std::string, std::string> &v) {RET_OUT_FN(ss_map_out  , &v);}

static void bool_in  (intmax_t src, cq_bool_out   out) {if (out) out(*(bool    *)&src);}
static void int8_in  (intmax_t src, cq_int8_out   out) {if (out) out(*(int8_t  *)&src);}
static void int16_in (intmax_t src, cq_int16_out  out) {if (out) out(*(int16_t *)&src);}
static void int32_in (intmax_t src, cq_int32_out  out) {if (out) out(*(int32_t *)&src);}
static void int64_in (intmax_t src, cq_int64_out  out) {if (out) out(*(int64_t *)&src);}
static void float_in (intmax_t src, cq_float_out  out) {if (out) out(*(float   *)&src);}
static void double_in(intmax_t src, cq_double_out out) {if (out) out(*(double  *)&src);}

static void str_in(intmax_t src, cq_str_out out) {
    if (src == 0) {
        return;
    }
    auto object = reinterpret_cast<const std::string *>(src);
    if (out != NULL) {
        out(object->c_str());
    }
}

static void bytes_in(intmax_t src, cq_bytes_out out) {
    if (src == 0) {
        return;
    }
    auto object = reinterpret_cast<const std::vector<uint8_t> *>(src);
    if (out != NULL) {
        out(object->data(), (int32_t)object->size());
    }
}

static void i64_list_in(intmax_t src, cq_i64_list_out out) {
    if (src == 0) {
        return;
    }
    auto object = reinterpret_cast<const std::vector<int64_t> *>(src);
    if (out != NULL) {
        for (int64_t it : *object) {
            out(it);
        }
    }
}

static void str_list_in(intmax_t src, cq_str_list_out out) {
    if (src == 0) {
        return;
    }
    auto object = reinterpret_cast<const std::vector<std::string> *>(src);
    if (out != NULL) {
        for (const std::string &it : *object) {
            out(it.c_str());
        }
    }
}

static void ss_map_in(intmax_t src, cq_ss_map_out out) {
    if (src == 0) {
        return;
    }
    auto object = reinterpret_cast<const std::map<std::string, std::string> *>(src);
    if (out != NULL) {
        for (auto &cp : *object) {
            out(cp.first.c_str(), cp.second.c_str());
        }
    }
}

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

cq_bool_in   cq_cpp_in(bool    value) {RET_IN_FN(bool_in  , value);}
cq_int8_in   cq_cpp_in(int8_t  value) {RET_IN_FN(int8_in  , value);}
cq_int16_in  cq_cpp_in(int16_t value) {RET_IN_FN(int16_in , value);}
cq_int32_in  cq_cpp_in(int32_t value) {RET_IN_FN(int32_in , value);}
cq_int64_in  cq_cpp_in(int64_t value) {RET_IN_FN(int64_in , value);}
cq_float_in  cq_cpp_in(float   value) {RET_IN_FN(float_in , value);}
cq_double_in cq_cpp_in(double  value) {RET_IN_FN(double_in, value);}

cq_str_in      cq_cpp_in(const std::string                        &v) {RET_IN_FN(str_in     , v);}
cq_bytes_in    cq_cpp_in(const std::vector<uint8_t>               &v) {RET_IN_FN(bytes_in   , v);}
cq_i64_list_in cq_cpp_in(const std::vector<int64_t>               &v) {RET_IN_FN(i64_list_in, v);}
cq_str_list_in cq_cpp_in(const std::vector<std::string>           &v) {RET_IN_FN(str_list_in, v);}
cq_ss_map_in   cq_cpp_in(const std::map<std::string, std::string> &v) {RET_IN_FN(ss_map_in  , v);}

template<class R, class F> R cpp_v(F in) {
    R object{};
    if (in != NULL) {
        in(cq_cpp_out(object));
    }
    return object;
}

bool    cq_cpp_bool  (cq_bool_in   in) {return cpp_v<bool   >(in);}
int8_t  cq_cpp_int8  (cq_int8_in   in) {return cpp_v<int8_t >(in);}
int16_t cq_cpp_int16 (cq_int16_in  in) {return cpp_v<int16_t>(in);}
int32_t cq_cpp_int32 (cq_int32_in  in) {return cpp_v<int32_t>(in);}
int64_t cq_cpp_int64 (cq_int64_in  in) {return cpp_v<int64_t>(in);}
float   cq_cpp_float (cq_float_in  in) {return cpp_v<float  >(in);}
double  cq_cpp_double(cq_double_in in) {return cpp_v<double >(in);}

std::string                        cq_cpp_str     (cq_str_in      in) {return cpp_v<std::string                       >(in);}
std::vector<uint8_t>               cq_cpp_bytes   (cq_bytes_in    in) {return cpp_v<std::vector<uint8_t>              >(in);}
std::vector<int64_t>               cq_cpp_i64_list(cq_i64_list_in in) {return cpp_v<std::vector<int64_t>              >(in);}
std::vector<std::string>           cq_cpp_str_list(cq_str_list_in in) {return cpp_v<std::vector<std::string>          >(in);}
std::map<std::string, std::string> cq_cpp_ss_map  (cq_ss_map_in   in) {return cpp_v<std::map<std::string, std::string>>(in);}

template<class T, class F> void cpp_set(T value, F out) {
    if (out != NULL) {
        cq_cpp_in(value)(out);
    }
}

void cq_cpp_set(bool    value, cq_bool_out   out) {cpp_set(value, out);}
void cq_cpp_set(int8_t  value, cq_int8_out   out) {cpp_set(value, out);}
void cq_cpp_set(int16_t value, cq_int16_out  out) {cpp_set(value, out);}
void cq_cpp_set(int32_t value, cq_int32_out  out) {cpp_set(value, out);}
void cq_cpp_set(int64_t value, cq_int64_out  out) {cpp_set(value, out);}
void cq_cpp_set(float   value, cq_float_out  out) {cpp_set(value, out);}
void cq_cpp_set(double  value, cq_double_out out) {cpp_set(value, out);}

void cq_cpp_set(const std::string                        &value, cq_str_out      out) {cpp_set(value, out);}
void cq_cpp_set(const std::vector<uint8_t>               &value, cq_bytes_out    out) {cpp_set(value, out);}
void cq_cpp_set(const std::vector<int64_t>               &value, cq_i64_list_out out) {cpp_set(value, out);}
void cq_cpp_set(const std::vector<std::string>           &value, cq_str_list_out out) {cpp_set(value, out);}
void cq_cpp_set(const std::map<std::string, std::string> &value, cq_ss_map_out   out) {cpp_set(value, out);}

//block:

template<class T> void block_in(const std::string name, cq_type type, T value) {
    auto ptr = (void *)cq_cpp_in(value);
    cq_set_block_param(name.c_str(), type, ptr);
}

void cq_cpp_block_in(const std::string &n, bool    v) {block_in(n, CQ_TYPE_BOOL_IN  , v);}
void cq_cpp_block_in(const std::string &n, int8_t  v) {block_in(n, CQ_TYPE_INT8_IN  , v);}
void cq_cpp_block_in(const std::string &n, int16_t v) {block_in(n, CQ_TYPE_INT16_IN , v);}
void cq_cpp_block_in(const std::string &n, int32_t v) {block_in(n, CQ_TYPE_INT32_IN , v);}
void cq_cpp_block_in(const std::string &n, int64_t v) {block_in(n, CQ_TYPE_INT64_IN , v);}
void cq_cpp_block_in(const std::string &n, float   v) {block_in(n, CQ_TYPE_FLOAT_IN , v);}
void cq_cpp_block_in(const std::string &n, double  v) {block_in(n, CQ_TYPE_DOUBLE_IN, v);}

void cq_cpp_block_in(const std::string &n, const std::string                        &v) {block_in(n, CQ_TYPE_STR_IN     , v);}
void cq_cpp_block_in(const std::string &n, const std::vector<uint8_t>               &v) {block_in(n, CQ_TYPE_BYTES_IN   , v);}
void cq_cpp_block_in(const std::string &n, const std::vector<int64_t>               &v) {block_in(n, CQ_TYPE_I64_LIST_IN, v);}
void cq_cpp_block_in(const std::string &n, const std::vector<std::string>           &v) {block_in(n, CQ_TYPE_STR_LIST_IN, v);}
void cq_cpp_block_in(const std::string &n, const std::map<std::string, std::string> &v) {block_in(n, CQ_TYPE_SS_MAP_IN  , v);}

template<class T> void block_out(const std::string name, cq_type type, T value) {
    auto ptr = (void *)cq_cpp_out(value);
    cq_set_block_param(name.c_str(), type, ptr);
}

void cq_cpp_block_out(const std::string &n, bool    &v) {block_out(n, CQ_TYPE_BOOL_OUT  , v);}
void cq_cpp_block_out(const std::string &n, int8_t  &v) {block_out(n, CQ_TYPE_INT8_OUT  , v);}
void cq_cpp_block_out(const std::string &n, int16_t &v) {block_out(n, CQ_TYPE_INT16_OUT , v);}
void cq_cpp_block_out(const std::string &n, int32_t &v) {block_out(n, CQ_TYPE_INT32_OUT , v);}
void cq_cpp_block_out(const std::string &n, int64_t &v) {block_out(n, CQ_TYPE_INT64_OUT , v);}
void cq_cpp_block_out(const std::string &n, float   &v) {block_out(n, CQ_TYPE_FLOAT_OUT , v);}
void cq_cpp_block_out(const std::string &n, double  &v) {block_out(n, CQ_TYPE_DOUBLE_OUT, v);}

void cq_cpp_block_out(const std::string &n, std::string                        &v) {block_out(n, CQ_TYPE_STR_OUT     , v);}
void cq_cpp_block_out(const std::string &n, std::vector<uint8_t>               &v) {block_out(n, CQ_TYPE_BYTES_OUT   , v);}
void cq_cpp_block_out(const std::string &n, std::vector<int64_t>               &v) {block_out(n, CQ_TYPE_I64_LIST_OUT, v);}
void cq_cpp_block_out(const std::string &n, std::vector<std::string>           &v) {block_out(n, CQ_TYPE_STR_LIST_OUT, v);}
void cq_cpp_block_out(const std::string &n, std::map<std::string, std::string> &v) {block_out(n, CQ_TYPE_SS_MAP_OUT  , v);}

template<class IN, class RET> auto block_p(const std::string name, cq_type type, RET ret) -> decltype(ret(nullptr)) {
    IN in = (IN)cq_block_param(name.c_str(), type);
    return ret(in);
}

bool    cq_cpp_block_bool  (const std::string &n) {return block_p<cq_bool_in  >(n, CQ_TYPE_BOOL_IN  , cq_cpp_bool  );}
int8_t  cq_cpp_block_int8  (const std::string &n) {return block_p<cq_int8_in  >(n, CQ_TYPE_INT8_IN  , cq_cpp_int8  );}
int16_t cq_cpp_block_int16 (const std::string &n) {return block_p<cq_int16_in >(n, CQ_TYPE_INT16_IN , cq_cpp_int16 );}
int32_t cq_cpp_block_int32 (const std::string &n) {return block_p<cq_int32_in >(n, CQ_TYPE_INT32_IN , cq_cpp_int32 );}
int64_t cq_cpp_block_int64 (const std::string &n) {return block_p<cq_int64_in >(n, CQ_TYPE_INT64_IN , cq_cpp_int64 );}
float   cq_cpp_block_float (const std::string &n) {return block_p<cq_float_in >(n, CQ_TYPE_FLOAT_IN , cq_cpp_float );}
double  cq_cpp_block_double(const std::string &n) {return block_p<cq_double_in>(n, CQ_TYPE_DOUBLE_IN, cq_cpp_double);}

std::string                        cq_cpp_block_str     (const std::string &n) {return block_p<cq_str_in     >(n, CQ_TYPE_STR_IN     , cq_cpp_str     );}
std::vector<uint8_t>               cq_cpp_block_bytes   (const std::string &n) {return block_p<cq_bytes_in   >(n, CQ_TYPE_BYTES_IN   , cq_cpp_bytes   );}
std::vector<int64_t>               cq_cpp_block_i64_list(const std::string &n) {return block_p<cq_i64_list_in>(n, CQ_TYPE_I64_LIST_IN, cq_cpp_i64_list);}
std::vector<std::string>           cq_cpp_block_str_list(const std::string &n) {return block_p<cq_str_list_in>(n, CQ_TYPE_STR_LIST_IN, cq_cpp_str_list);}
std::map<std::string, std::string> cq_cpp_block_ss_map  (const std::string &n) {return block_p<cq_ss_map_in  >(n, CQ_TYPE_SS_MAP_IN  , cq_cpp_ss_map  );}

template<class OUT, class T> void block_set(const std::string &name, cq_type type, T value) {
    OUT out = (OUT)cq_block_param(name.c_str(), type);
    cq_cpp_set(value, out);
}

void cq_cpp_block_set(const std::string &n, bool    v) {block_set<cq_bool_out  >(n, CQ_TYPE_BOOL_OUT  , v);}
void cq_cpp_block_set(const std::string &n, int8_t  v) {block_set<cq_int8_out  >(n, CQ_TYPE_INT8_OUT  , v);}
void cq_cpp_block_set(const std::string &n, int16_t v) {block_set<cq_int16_out >(n, CQ_TYPE_INT16_OUT , v);}
void cq_cpp_block_set(const std::string &n, int32_t v) {block_set<cq_int32_out >(n, CQ_TYPE_INT32_OUT , v);}
void cq_cpp_block_set(const std::string &n, int64_t v) {block_set<cq_int64_out >(n, CQ_TYPE_INT64_OUT , v);}
void cq_cpp_block_set(const std::string &n, float   v) {block_set<cq_float_out >(n, CQ_TYPE_FLOAT_OUT , v);}
void cq_cpp_block_set(const std::string &n, double  v) {block_set<cq_double_out>(n, CQ_TYPE_DOUBLE_OUT, v);}

void cq_cpp_block_set(const std::string &n, const std::string                        &v) {block_set<cq_str_out     >(n, CQ_TYPE_STR_OUT     , v);}
void cq_cpp_block_set(const std::string &n, const std::vector<uint8_t>               &v) {block_set<cq_bytes_out   >(n, CQ_TYPE_BYTES_OUT   , v);}
void cq_cpp_block_set(const std::string &n, const std::vector<int64_t>               &v) {block_set<cq_i64_list_out>(n, CQ_TYPE_I64_LIST_OUT, v);}
void cq_cpp_block_set(const std::string &n, const std::vector<std::string>           &v) {block_set<cq_str_list_out>(n, CQ_TYPE_STR_LIST_OUT, v);}
void cq_cpp_block_set(const std::string &n, const std::map<std::string, std::string> &v) {block_set<cq_ss_map_out  >(n, CQ_TYPE_SS_MAP_OUT  , v);}

//object reference:

static const int32_t CPP_OBJECT_MAGIC = 0x432B2B; //"C++".

static void release_raw_cpp(void *raw) {
    if (raw != nullptr) {
        delete (cqObjectRef *)raw;
    }
}

cq_obj *cq_obj_retain_cpp(cqObjectRef object, const std::string &cls) {
    if (object == nullptr) {
        return nullptr;
    }
    
    void *raw = new cqObjectRef(object);
    cq_obj *ptr = cq_obj_retain_raw(raw, release_raw_cpp);
    
    if (!cls.empty()) {
        cq_obj_set_cls(ptr, cls.c_str());
    }
    cq_obj_set_magic(ptr, CPP_OBJECT_MAGIC);
    
    return ptr;
}

cqObjectRef cq_obj_raw_cpp(cq_obj *ptr, cqClass *cls) {
    if (ptr == nullptr) {
        return nullptr;
    }
    
    if (cq_obj_magic(ptr) != CPP_OBJECT_MAGIC) {
        //it's not a c++ object.
        return nullptr;
    }
    
    auto raw = (cqObjectRef *)cq_obj_raw(ptr);
    if (cls && raw->get()->dynamicClass() != cls) {
        //it's not wanted class.
        return nullptr;
    }
    
    return cqObjectRef(*raw);
}

_CQBASIS_END_VERSION_NS
