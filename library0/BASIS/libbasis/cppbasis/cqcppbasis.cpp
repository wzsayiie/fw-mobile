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

cq_bytes_out    cq_cpp_out(std::vector<uint8_t>               &v) {RET_OUT_FN(bytes_out   , &v);}
cq_i64_list_out cq_cpp_out(std::vector<int64_t>               &v) {RET_OUT_FN(i64_list_out, &v);}
cq_str_list_out cq_cpp_out(std::vector<std::string>           &v) {RET_OUT_FN(str_list_out, &v);}
cq_ss_map_out   cq_cpp_out(std::map<std::string, std::string> &v) {RET_OUT_FN(ss_map_out  , &v);}

static void bytes_in(const void *src, cq_bytes_out out) {
    if (src == 0) {
        return;
    }
    auto object = (const std::vector<uint8_t> *)src;
    if (out != NULL) {
        out(object->data(), (int32_t)object->size());
    }
}

static void i64_list_in(const void *src, cq_i64_list_out out) {
    if (src == 0) {
        return;
    }
    auto object = (const std::vector<int64_t> *)src;
    if (out != NULL) {
        for (int64_t it : *object) {
            out(it);
        }
    }
}

static void str_list_in(const void *src, cq_str_list_out out) {
    if (src == 0) {
        return;
    }
    auto object = (const std::vector<std::string> *)src;
    if (out != NULL) {
        for (const std::string &it : *object) {
            out(it.c_str());
        }
    }
}

static void ss_map_in(const void *src, cq_ss_map_out out) {
    if (src == 0) {
        return;
    }
    auto object = (const std::map<std::string, std::string> *)src;
    if (out != NULL) {
        for (auto &cp : *object) {
            out(cp.first.c_str(), cp.second.c_str());
        }
    }
}

#define GEN_IN_FN(FN, PARAM, ...)\
/**/    static thread_local const void *FN##_src_0 = 0;\
/**/    static thread_local const void *FN##_src_1 = 0;\
/**/    static thread_local const void *FN##_src_2 = 0;\
/**/    static thread_local const void *FN##_src_3 = 0;\
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

cq_bytes_in    cq_cpp_in(const std::vector<uint8_t>               &v) {RET_IN_FN(bytes_in   , &v);}
cq_i64_list_in cq_cpp_in(const std::vector<int64_t>               &v) {RET_IN_FN(i64_list_in, &v);}
cq_str_list_in cq_cpp_in(const std::vector<std::string>           &v) {RET_IN_FN(str_list_in, &v);}
cq_ss_map_in   cq_cpp_in(const std::map<std::string, std::string> &v) {RET_IN_FN(ss_map_in  , &v);}

template<class R, class F> R cpp_v(F in) {
    R object{};
    if (in != NULL) {
        in(cq_cpp_out(object));
    }
    return object;
}

std::vector<uint8_t>               cq_cpp_bytes   (cq_bytes_in    in) {return cpp_v<std::vector<uint8_t>              >(in);}
std::vector<int64_t>               cq_cpp_i64_list(cq_i64_list_in in) {return cpp_v<std::vector<int64_t>              >(in);}
std::vector<std::string>           cq_cpp_str_list(cq_str_list_in in) {return cpp_v<std::vector<std::string>          >(in);}
std::map<std::string, std::string> cq_cpp_ss_map  (cq_ss_map_in   in) {return cpp_v<std::map<std::string, std::string>>(in);}

template<class T, class F> void cpp_set(T value, F out) {
    if (out != NULL) {
        cq_cpp_in(value)(out);
    }
}

void cq_cpp_set(const std::vector<uint8_t>               &value, cq_bytes_out    out) {cpp_set(value, out);}
void cq_cpp_set(const std::vector<int64_t>               &value, cq_i64_list_out out) {cpp_set(value, out);}
void cq_cpp_set(const std::vector<std::string>           &value, cq_str_list_out out) {cpp_set(value, out);}
void cq_cpp_set(const std::map<std::string, std::string> &value, cq_ss_map_out   out) {cpp_set(value, out);}

//cpp block:

static void run_block(void *raw) {
    if (raw != nullptr) {
        auto func = (std::function<void ()> *)raw;
        (*func)();
    }
}

static void del_block(void *raw) {
    auto func = (std::function<void ()> *)raw;
    delete func;
}

cq_block *cq_block_retain_cpp(std::function<void ()> func) {
    if (func != nullptr) {
        auto raw = new std::function<void ()>(func);
        return cq_block_retain_raw(raw, run_block, del_block);
    }
    return nullptr;
}

//bridged cpp object:

static const int32_t CPP_OBJECT_MAGIC = 0x432B2B; //"C++".

static void del_bridge(void *raw) {
    delete (cqObjectRef *)raw;
}

cq_bridge *cq_bridge_retain_cpp(cqObjectRef object, const std::string &cls) {
    if (object != nullptr) {
        void *raw = new cqObjectRef(object);
        return cq_bridge_retain_raw(raw, cls.c_str(), CPP_OBJECT_MAGIC, del_bridge);
    }
    return nullptr;
}

cqObjectRef cq_bridge_cpp(cq_bridge *bridge, cqClass *cls) {
    if (bridge == nullptr) {
        return nullptr;
    }
    
    if (cq_bridge_magic(bridge) != CPP_OBJECT_MAGIC) {
        //it's not a c++ object.
        return nullptr;
    }
    
    auto raw = (cqObjectRef *)cq_bridge_raw(bridge);
    if (cls && raw->get()->dynamicClass() != cls) {
        //it's not wanted class.
        return nullptr;
    }
    
    return cqObjectRef(*raw);
}

_CQBASIS_END_VERSION_NS
