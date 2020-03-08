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

using Bytes    = std::vector<uint8_t>;
using INT_LIST = std::vector<int64_t>;
using STR_LIST = std::vector<std::string>;
using SS_MAP   = std::map<std::string, std::string>;

static thread_local Bytes    *_dst_bytes    = nullptr;
static thread_local INT_LIST *_dst_int_list = nullptr;
static thread_local STR_LIST *_dst_str_list = nullptr;
static thread_local SS_MAP   *_dst_ss_map   = nullptr;

static void bytes_out(const void *bytes, int32_t len) {
    if (_dst_bytes != nullptr) {
        auto ptr = (const uint8_t *)bytes;
        auto dat = _dst_bytes;
        
        if (ptr && len > 0) {
            dat->assign(ptr, ptr + len);
        } else {
            dat->clear();
        }
    }
}

static void int_list_out(int64_t item) {
    if (_dst_int_list != nullptr) {
        _dst_int_list->push_back(item);
    }
}

static void str_list_out(const char *item) {
    if (_dst_str_list != nullptr) {
        _dst_str_list->push_back(cqString::make(item));
    }
}

static void ss_map_out(const char *key, const char *value) {
    if (_dst_ss_map && !cq_str_empty(key)) {
        (*_dst_ss_map)[key] = cqString::make(value);
    }
}

static thread_local const Bytes    *_src_bytes    = nullptr;
static thread_local const INT_LIST *_src_int_list = nullptr;
static thread_local const STR_LIST *_src_str_list = nullptr;
static thread_local const SS_MAP   *_src_ss_map   = nullptr;

static void bytes_in(cq_bytes_out out) {
    if (!_src_bytes && !out) {
        return;
    }
    out(_src_bytes->data(), (int32_t)_src_bytes->size());
}

static void int_list_in(cq_i64_list_out out) {
    if (!_src_int_list && !out) {
        return;
    }
    for (int64_t it : *_src_int_list) {
        out(it);
    }
}

static void str_list_in(cq_str_list_out out) {
    if (!_src_str_list && !out) {
        return;
    }
    for (const std::string &it : *_src_str_list) {
        out(it.c_str());
    }
}

static void ss_map_in(cq_ss_map_out out) {
    if (!_src_ss_map && !out) {
        return;
    }
    for (auto &cp : *_src_ss_map) {
        out(cp.first.c_str(), cp.second.c_str());
    }
}

cq_bytes_out    cq_cpp_bytes_out   (Bytes    &a) {_dst_bytes    = &a; return bytes_out   ;}
cq_i64_list_out cq_cpp_i64_list_out(INT_LIST &a) {_dst_int_list = &a; return int_list_out;}
cq_str_list_out cq_cpp_str_list_out(STR_LIST &a) {_dst_str_list = &a; return str_list_out;}
cq_ss_map_out   cq_cpp_ss_map_out  (SS_MAP   &a) {_dst_ss_map   = &a; return ss_map_out  ;}

cq_bytes_in    cq_cpp_bytes_in   (const Bytes    &a) {_src_bytes    = &a; return bytes_in   ;}
cq_i64_list_in cq_cpp_i64_list_in(const INT_LIST &a) {_src_int_list = &a; return int_list_in;}
cq_str_list_in cq_cpp_str_list_in(const STR_LIST &a) {_src_str_list = &a; return str_list_in;}
cq_ss_map_in   cq_cpp_ss_map_in  (const SS_MAP   &a) {_src_ss_map   = &a; return ss_map_in  ;}

#define KEEP(VALUE, CODE)\
/**/    do{\
/**/        auto __last = VALUE;\
/**/        CODE\
/**/        VALUE = __last;\
/**/    } while (0)

Bytes cq_cpp_bytes_from(cq_bytes_in in) {
    Bytes object;
    if (in != nullptr) {
        //NOTE: hold last value of _dst_bytes.
        //the function shouldn't affect last cq_cpp_bytes_out() call.
        KEEP(_dst_bytes, {
            in(cq_cpp_bytes_out(object));
        });
    }
    return object;
}

INT_LIST cq_cpp_i64_list_from(cq_i64_list_in in) {
    INT_LIST object;
    if (in != nullptr) {
        KEEP(_dst_int_list, {
            in(cq_cpp_i64_list_out(object));
        });
    }
    return object;
}

STR_LIST cq_cpp_str_list_from(cq_str_list_in in) {
    STR_LIST object;
    if (in != nullptr) {
        KEEP(_dst_str_list, {
            in(cq_cpp_str_list_out(object));
        });
    }
    return object;
}

SS_MAP cq_cpp_ss_map_from(cq_ss_map_in in) {
    SS_MAP object;
    if (in != nullptr) {
        KEEP(_dst_ss_map, {
            in(cq_cpp_ss_map_out(object));
        });
    }
    return object;
}

void cq_cpp_bytes_assign(const Bytes &object, cq_bytes_out out) {
    KEEP(_src_bytes, {
        cq_cpp_bytes_in(object)(out);
    });
}

void cq_cpp_i64_list_assign(const INT_LIST &object, cq_i64_list_out out) {
    KEEP(_src_int_list, {
        cq_cpp_i64_list_in(object)(out);
    });
}

void cq_cpp_str_list_assign(const STR_LIST &object, cq_str_list_out out) {
    KEEP(_src_str_list, {
        cq_cpp_str_list_in(object)(out);
    });
}

void cq_cpp_ss_map_assign(const SS_MAP &object, cq_ss_map_out out) {
    KEEP(_src_ss_map, {
        cq_cpp_ss_map_in(object)(out);
    });
}

//object reference:

static const int32_t CPPObjectMagic = 0x432B2B; //"C++".

static void release_raw_cpp(void *raw) {
    if (raw != nullptr) {
        delete (cqObjectRef *)raw;
    }
}

cq_obj *cq_retain_cpp_obj(cqObjectRef object, const std::string &cls) {
    if (object == nullptr) {
        return nullptr;
    }
    
    void *raw = new cqObjectRef(object);
    cq_obj *ptr = cq_retain_raw_obj(raw, release_raw_cpp);
    
    if (!cls.empty()) {
        cq_set_obj_cls(ptr, cls.c_str());
    }
    cq_set_obj_magic(ptr, CPPObjectMagic);
    
    return ptr;
}

cqObjectRef cq_obj_raw_cpp(cq_obj *ptr, cqClass *cls) {
    if (ptr == nullptr) {
        return nullptr;
    }
    
    if (cq_obj_magic(ptr) != CPPObjectMagic) {
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
