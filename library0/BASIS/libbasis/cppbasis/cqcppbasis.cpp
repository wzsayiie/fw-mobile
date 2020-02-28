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

cq_bytes   *cq_bytes_cast_cpp  (const std::vector<uint8_t>               &a) {return (cq_bytes   *)&a;}
cq_int64s  *cq_int64s_cast_cpp (const std::vector<int64_t>               &a) {return (cq_int64s  *)&a;}
cq_strings *cq_strings_cast_cpp(const std::vector<std::string>           &a) {return (cq_strings *)&a;}
cq_ss_map  *cq_ss_map_cast_cpp (const std::map<std::string, std::string> &a) {return (cq_ss_map  *)&a;}

void cq_cpp_bytes_receiver  (cq_bytes   *a, const void *b, int32_t     c) {cq_c_bytes_receiver  (a, b, c);}
void cq_cpp_int64s_receiver (cq_int64s  *a, int64_t     b               ) {cq_c_int64s_receiver (a, b   );}
void cq_cpp_strings_receiver(cq_strings *a, const char *b               ) {cq_c_strings_receiver(a, b   );}
void cq_cpp_ss_map_receiver (cq_ss_map  *a, const char *b, const char *c) {cq_c_ss_map_receiver (a, b, c);}

void cq_cpp_bytes_sender  (cq_bytes   *a, cq_bytes_receiver   b, cq_bytes   *c) {cq_c_bytes_sender  (a, b, c);}
void cq_cpp_int64s_sender (cq_int64s  *a, cq_int64s_receiver  b, cq_int64s  *c) {cq_c_int64s_sender (a, b, c);}
void cq_cpp_strings_sender(cq_strings *a, cq_strings_receiver b, cq_strings *c) {cq_c_strings_sender(a, b, c);}
void cq_cpp_ss_map_sender (cq_ss_map  *a, cq_ss_map_receiver  b, cq_ss_map  *c) {cq_c_ss_map_sender (a, b, c);}

std::vector<uint8_t> cq_cpp_bytes_from(cq_bytes_sender send, cq_bytes *src) {
    std::vector<uint8_t> object;
    if (send) {
        send(src, cq_cpp_bytes_receiver, cq_bytes_cast_cpp(object));
    }
    return object;
}

std::vector<int64_t> cq_cpp_int64s_from(cq_int64s_sender send, cq_int64s *src) {
    std::vector<int64_t> object;
    if (send) {
        send(src, cq_cpp_int64s_receiver, cq_int64s_cast_cpp(object));
    }
    return object;
}

std::vector<std::string> cq_cpp_strings_from(cq_strings_sender send, cq_strings *src) {
    std::vector<std::string> object;
    if (send) {
        send(src, cq_cpp_strings_receiver, cq_strings_cast_cpp(object));
    }
    return object;
}

std::map<std::string, std::string> cq_cpp_ss_map_from(cq_ss_map_sender send, cq_ss_map *src) {
    std::map<std::string, std::string> object;
    if (send) {
        send(src, cq_cpp_ss_map_receiver, cq_ss_map_cast_cpp(object));
    }
    return object;
}

void cq_send_cpp_bytes(const std::vector<uint8_t> &src, cq_bytes_receiver recv, cq_bytes *dst) {
    cq_cpp_bytes_sender(cq_bytes_cast_cpp(src), recv, dst);
}

void cq_send_cpp_int64s(const std::vector<int64_t> &src, cq_int64s_receiver recv, cq_int64s *dst) {
    cq_cpp_int64s_sender(cq_int64s_cast_cpp(src), recv, dst);
}

void cq_send_cpp_strings(const std::vector<std::string> &src, cq_strings_receiver recv, cq_strings *dst) {
    cq_cpp_strings_sender(cq_strings_cast_cpp(src), recv, dst);
}

void cq_send_cpp_ss_map(const std::map<std::string, std::string> &src, cq_ss_map_receiver recv, cq_ss_map *dst) {
    cq_cpp_ss_map_sender(cq_ss_map_cast_cpp(src), recv, dst);
}

cq_bytes *cq_store_cpp_bytes(const std::vector<uint8_t> &object) {
    return cq_store_c_bytes(cq_cpp_bytes_sender, cq_bytes_cast_cpp(object));
}

cq_int64s *cq_store_cpp_int64s(const std::vector<int64_t> &object) {
    return cq_store_c_int64s(cq_cpp_int64s_sender, cq_int64s_cast_cpp(object));
}

cq_strings *cq_store_cpp_strings(const std::vector<std::string> &object) {
    return cq_store_c_strings(cq_cpp_strings_sender, cq_strings_cast_cpp(object));
}

cq_ss_map *cq_store_cpp_ss_map(const std::map<std::string, std::string> &object) {
    return cq_store_c_ss_map(cq_cpp_ss_map_sender, cq_ss_map_cast_cpp(object));
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
