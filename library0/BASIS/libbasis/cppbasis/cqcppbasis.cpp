#include "cqcppbasis.hh"

//std extension:

std::string cqString::make(const char *value) {
    return value ? value : "";
}

bool cqString::empty(const char *value) {
    return value == nullptr || *value == '\0';
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

//interfaces for interaction with c:

cq_bytes   *cq_cpp::bytes  (const std::vector<uint8_t>               &a) {return (cq_bytes   *)&a;}
cq_int64s  *cq_cpp::int64s (const std::vector<int64_t>               &a) {return (cq_int64s  *)&a;}
cq_strings *cq_cpp::strings(const std::vector<std::string>           &a) {return (cq_strings *)&a;}
cq_ss_map  *cq_cpp::ss_map (const std::map<std::string, std::string> &a) {return (cq_ss_map  *)&a;}

void cq_cpp::bytes_recv  (cq_bytes   *a, const void *b, int32_t     c) {cq_c_bytes_recv  (a, b, c);}
void cq_cpp::int64s_recv (cq_int64s  *a, int64_t     b               ) {cq_c_int64s_recv (a, b   );}
void cq_cpp::strings_recv(cq_strings *a, const char *b               ) {cq_c_strings_recv(a, b   );}
void cq_cpp::ss_map_recv (cq_ss_map  *a, const char *b, const char *c) {cq_c_ss_map_recv (a, b, c);}

void cq_cpp::bytes_send  (cq_bytes   *a, cq_bytes_recv   b, cq_bytes   *c) {cq_c_bytes_send  (a, b, c);}
void cq_cpp::int64s_send (cq_int64s  *a, cq_int64s_recv  b, cq_int64s  *c) {cq_c_int64s_send (a, b, c);}
void cq_cpp::strings_send(cq_strings *a, cq_strings_recv b, cq_strings *c) {cq_c_strings_send(a, b, c);}
void cq_cpp::ss_map_send (cq_ss_map  *a, cq_ss_map_recv  b, cq_ss_map  *c) {cq_c_ss_map_send (a, b, c);}

std::vector<uint8_t> cq_cpp::from(cq_bytes_send send, cq_bytes *src) {
    std::vector<uint8_t> object;
    if (send) {
        send(src, bytes_recv, bytes(object));
    }
    return object;
}

std::vector<int64_t> cq_cpp::from(cq_int64s_send send, cq_int64s *src) {
    std::vector<int64_t> object;
    if (send) {
        send(src, int64s_recv, int64s(object));
    }
    return object;
}

std::vector<std::string> cq_cpp::from(cq_strings_send send, cq_strings *src) {
    std::vector<std::string> object;
    if (send) {
        send(src, strings_recv, strings(object));
    }
    return object;
}

std::map<std::string, std::string> cq_cpp::from(cq_ss_map_send send, cq_ss_map *src) {
    std::map<std::string, std::string> object;
    if (send) {
        send(src, ss_map_recv, ss_map(object));
    }
    return object;
}

void cq_cpp::send(const std::vector<uint8_t> &src, cq_bytes_recv recv, cq_bytes *dst) {
    bytes_send(bytes(src), recv, dst);
}

void cq_cpp::send(const std::vector<int64_t> &src, cq_int64s_recv recv, cq_int64s *dst) {
    int64s_send(int64s(src), recv, dst);
}

void cq_cpp::send(const std::vector<std::string> &src, cq_strings_recv recv, cq_strings *dst) {
    strings_send(strings(src), recv, dst);
}

void cq_cpp::send(const std::map<std::string, std::string> &src, cq_ss_map_recv recv, cq_ss_map *dst) {
    ss_map_send(ss_map(src), recv, dst);
}

cq_bytes *cq_cpp::store(const std::vector<uint8_t> &object) {
    return cq_store_bytes(bytes_send, bytes(object));
}

cq_int64s *cq_cpp::store(const std::vector<int64_t> &object) {
    return cq_store_int64s(int64s_send, int64s(object));
}

cq_strings *cq_cpp::store(const std::vector<std::string> &object) {
    return cq_store_strings(strings_send, strings(object));
}

cq_ss_map *cq_cpp::store(const std::map<std::string, std::string> &object) {
    return cq_store_ss_map(ss_map_send, ss_map(object));
}
