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

template<class T> void x_clear(void *dst) {
    auto object = (T *)dst;
    object->clear();
}

static void bytes_clear     (void *dst) { x_clear<std::vector<uint8_t                 >>(dst); }
static void int64_list_clear(void *dst) { x_clear<std::vector<int64_t                 >>(dst); }
static void str_list_clear  (void *dst) { x_clear<std::vector<std::string             >>(dst); }
static void ss_map_clear    (void *dst) { x_clear<std::map   <std::string, std::string>>(dst); }

static void bytes_recv(void *dst, const void *bytes, int32_t length) {
    auto object = (std::vector<uint8_t> *)dst;
    
    if (bytes && length > 0) {
        object->assign((uint8_t *)bytes, (uint8_t *)bytes + length);
    }
}

static void int64_list_recv(void *dst, int64_t item) {
    auto object = (std::vector<int64_t> *)dst;
    
    object->push_back(item);
}

static void str_list_recv(void *dst, const char *item) {
    auto object = (std::vector<std::string> *)dst;
    
    object->push_back(cqString::make(item));
}

static void ss_map_recv(void *dst, const char *key, const char *value) {
    auto object = (std::map<std::string, std::string> *)dst;
    
    if (!cq_str_empty(key)) {
        (*object)[key] = cqString::make(value);
    }
}

static void bytes_send(void *src, cq_bytes *dst) {
    auto object = (const std::vector<uint8_t> *)src;
    
    dst->recv(dst->ref, object->data(), (int32_t)object->size());
}

static void int64_list_send(void *src, cq_int64_list *dst) {
    auto object = (const std::vector<int64_t> *)src;
    
    for (auto &it : *object) {
        dst->recv(dst->ref, it);
    }
}

static void str_list_send(void *src, cq_str_list *dst) {
    auto object = (const std::vector<std::string> *)src;
    
    for (auto &it : *object) {
        dst->recv(dst->ref, it.c_str());
    }
}

static void ss_map_send(void *src, cq_ss_map *dst) {
    auto object = (const std::map<std::string, std::string> *)src;
    
    for (auto &cp : *object) {
        dst->recv(dst->ref, cp.first.c_str(), cp.second.c_str());
    }
}

cq_bytes *cq_cpp_bytes(std::vector<uint8_t> &object) {
    auto ptr = (cq_bytes *)auto_alloc(sizeof(cq_bytes));
    
    ptr->clear = bytes_clear;
    ptr->recv  = bytes_recv;
    ptr->send  = bytes_send;
    ptr->ref   = &object;
    
    return ptr;
}

cq_int64_list *cq_cpp_int64_list(std::vector<int64_t> &object) {
    auto ptr = (cq_int64_list *)auto_alloc(sizeof(cq_int64_list));
    
    ptr->clear = int64_list_clear;
    ptr->recv  = int64_list_recv;
    ptr->send  = int64_list_send;
    ptr->ref   = &object;
    
    return ptr;
}

cq_str_list *cq_cpp_str_list(std::vector<std::string> &object) {
    auto ptr = (cq_str_list *)auto_alloc(sizeof(cq_str_list));
    
    ptr->clear = str_list_clear;
    ptr->recv  = str_list_recv;
    ptr->send  = str_list_send;
    ptr->ref   = &object;
    
    return ptr;
}

cq_ss_map *cq_cpp_ss_map(std::map<std::string, std::string> &object) {
    auto ptr = (cq_ss_map *)auto_alloc(sizeof(cq_ss_map));
    
    ptr->clear = ss_map_clear;
    ptr->recv  = ss_map_recv;
    ptr->send  = ss_map_send;
    ptr->ref   = &object;
    
    return ptr;
}

cq_bytes *cq_cpp_bytes(const std::vector<uint8_t> &object) {
    auto ptr = (cq_bytes *)auto_alloc(sizeof(cq_bytes));
    
    ptr->send = bytes_send;
    ptr->ref  = (void *)&object;
    
    return ptr;
}

cq_int64_list *cq_cpp_int64_list(const std::vector<int64_t> &object) {
    auto ptr = (cq_int64_list *)auto_alloc(sizeof(cq_int64_list));
    
    ptr->send = int64_list_send;
    ptr->ref  = (void *)&object;
    
    return ptr;
}

cq_str_list *cq_cpp_str_list(const std::vector<std::string> &object) {
    auto ptr = (cq_str_list *)auto_alloc(sizeof(cq_str_list));
    
    ptr->send = str_list_send;
    ptr->ref  = (void *)&object;
    
    return ptr;
}

cq_ss_map *cq_cpp_ss_map(const std::map<std::string, std::string> &object) {
    auto ptr = (cq_ss_map *)auto_alloc(sizeof(cq_ss_map));
    
    ptr->send = ss_map_send;
    ptr->ref  = (void *)&object;
    
    return ptr;
}

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

static void del_cpp_object(void *raw) {
    delete (cqObjectRef *)raw;
}

cq_object *cq_object_retain_cpp(cqObjectRef object, const std::string &cls) {
    if (object != nullptr) {
        void *raw = new cqObjectRef(object);
        return cq_object_retain_raw(raw, cls.c_str(), CPP_OBJECT_MAGIC, del_cpp_object);
    }
    return nullptr;
}

cqObjectRef cq_object_cpp(cq_object *object, cqClass *cls) {
    if (object == nullptr) {
        return nullptr;
    }
    
    if (cq_object_magic(object) != CPP_OBJECT_MAGIC) {
        //it's not a c++ object.
        return nullptr;
    }
    
    auto raw = (cqObjectRef *)cq_object_raw(object);
    if (cls && raw->get()->dynamicClass() != cls) {
        //it's not wanted class.
        return nullptr;
    }
    
    return cqObjectRef(*raw);
}

_CQBASIS_END_VERSION_NS
