#pragma once

#include "cqcbasis.h"

//containers
#include <map>
#include <set>
#include <string>
#include <vector>

//function
#include <functional>

//smart pointer
#include <memory>

//thread mutex
#include <atomic>
#include <mutex>

//algorithm
#include <algorithm>

#include "_CQBASIS_VERSION.h"
_CQBASIS_BEGIN_VERSION_NS

//std extension:

struct cqString {
    static std::string make(const char *value);
    static bool empty(const char *value);
};

struct cqVector {
    
    template<class T> static bool contains(const std::vector<T> &vec, const T &elem) {
        return std::find(vec.begin(), vec.end(), elem) != vec.end();
    }
    template<class T> static bool dontContain(const std::vector<T> &vec, const T &elem) {
        return std::find(vec.begin(), vec.end(), elem) == vec.end();
    }
    
    template<class T> static void erase(std::vector<T> *vec, const T &elem) {
        if (vec == nullptr) {
            return;
        }
        auto discard = std::remove_if(vec->begin(), vec->end(), [&](const T &it) {
            return it == elem;
        });
        vec->erase(discard, vec->end());
    }
};

struct cqMap {
    template<class M, class K> static bool contains(const M &m, const K &k) {
        return m.find(k) != m.end();
    }
    template<class M, class K> static bool dontContain(const M &m, const K &k) {
        return m.find(k) == m.end();
    }
};

//synchronization lock:

struct cqMutex {
    static std::mutex *random(const void *hash);
};

#define cq_synchronize_obj(HASH, BLOCK)\
/**/    do {\
/**/        std::mutex *__cq_mutex = cqMutex::random(HASH);\
/**/        std::lock_guard<std::mutex> __cq_guard(*__cq_mutex);\
/**/        BLOCK\
/**/    } while (0)

#define cq_synchronize(BLOCK)\
/**/    do {\
/**/        static std::mutex __cq_mutex;\
/**/        std::lock_guard<std::mutex> __cq_guard(__cq_mutex);\
/**/        BLOCK\
/**/    } while (0)

//class:

template<class T> struct cqRef {
    typedef std::shared_ptr<T> Strong;
    typedef std::weak_ptr<T> Weak;
};

struct cqClass;
struct _cqBaseObject {
    cqRef<_cqBaseObject>::Weak thisWeakRef;
    
    void init();
    
    static  cqClass *superclass();
    static  cqClass *clazz();
    virtual cqClass *dynamicSuperclass();
    virtual cqClass *dynamicClass();
    
    virtual ~_cqBaseObject();
};

#define cq_declare(CLASS)\
/**/    struct CLASS;\
/**/    typedef cqRef<CLASS>::Strong CLASS##Ref;\
/**/    typedef cqRef<CLASS>::Weak CLASS##WeakRef;

#define cq_class(CLASS, SUPER)\
/**/    cq_declare(CLASS)\
/**/    struct CLASS : _cqSandWich<CLASS, SUPER>

template<class CLASS, class SUPER> struct _cqSandWich : SUPER {
    
    typedef SUPER super;
    
    //the struct implemented by macro cq_member()
    struct Dat;
    
    std::shared_ptr<Dat> dat;
    
    //the constructor implemented by macro cq_member()
    _cqSandWich();
    
    template<class... A> static typename cqRef<CLASS>::Strong create(A... a) {
        auto object = std::make_shared<CLASS>();
        object->thisWeakRef = object;
        object->init(a...);
        return object;
    }
    
    typename cqRef<CLASS>::Strong strongRef() const {
        auto ref = SUPER::thisWeakRef.lock();
        return std::static_pointer_cast<CLASS>(ref);
    }
    
    typename cqRef<CLASS>::Weak weakRef() const {
        auto ref = SUPER::thisWeakRef.lock();
        return std::static_pointer_cast<CLASS>(ref);
    }
    
    static cqClass *superclass() {
        return SUPER::clazz();
    }
    
    //the function implemented by macro cq_member()
    static cqClass *clazz();
    
    cqClass *dynamicSuperclass() override {
        return SUPER::clazz();
    }
    
    cqClass *dynamicClass() override {
        return CLASS::clazz();
    }
};

struct cqObject;
struct cqClass {
    
    cqClass *const superclass;
    const char *const name;
    cqRef<cqObject>::Strong (*const create)();
    
    bool isKindOfClass(cqClass *cls) const;
};

template<class T> cqRef<cqObject>::Strong _cqObjectCreator() {
    return T::create();
}
template<class T> cqClass *_cqClassGet(const char *name) {
    static cqClass cls = {
        T::superclass(),
        name,
        _cqObjectCreator<T>
    };
    return &cls;
}

#define cq_member(CLASS)\
/**/    template<> _cqSandWich<CLASS, CLASS::super>::_cqSandWich()\
/**/        : dat(std::make_shared<Dat>())\
/**/    {\
/**/    }\
/**/    template<> cqClass *_cqSandWich<CLASS, CLASS::super>::clazz() {\
/**/        return _cqClassGet<CLASS>(""#CLASS);\
/**/    }\
/**/    template<> struct _cqSandWich<CLASS, CLASS::super>::Dat

//object:

cq_class(cqObject, _cqBaseObject) {
    
    virtual bool isKindOfClass(cqClass *cls);
    virtual bool isMemberOfClass(cqClass *cls);
    
    template<class TO_TYPE, class FROM_REF>
    static typename cqRef<TO_TYPE>::Strong cast(FROM_REF from) {
        return std::static_pointer_cast<TO_TYPE>(from);
    }
};

//proxy:

cq_class(cqProxy, cqObject) {
    
    void init();
    void init(cqObjectRef core);
    
    virtual void setCore(cqObjectRef core);
    virtual cqObjectRef core();
};

#define cq_as_proxy_of(CLASS)\
/**/    cqRef<CLASS>::Strong castCore() {\
/**/        return cqObject::cast<CLASS>(core());\
/**/    }

//static object:

template<class T, int = 0> typename cqRef<T>::Strong cqStaticObject() {
    cq_synchronize({
        static typename cqRef<T>::Strong object;
        if (object == nullptr) {
            object = T::create();
        }
        return object;
    });
}

//data interfaces for interaction with c:

cq_bytes_out    cq_cpp_bytes_out   (std::vector<uint8_t>         &object);
cq_i64_list_out cq_cpp_i64_list_out(std::vector<int64_t>         &object);
cq_str_list_out cq_cpp_str_list_out(std::vector<std::string>     &object);
cq_ss_map_out   cq_cpp_ss_map_out  (std::map<std::string, std::string> &);

cq_bytes_in    cq_cpp_bytes_in   (const std::vector<uint8_t>         &object);
cq_i64_list_in cq_cpp_i64_list_in(const std::vector<int64_t>         &object);
cq_str_list_in cq_cpp_str_list_in(const std::vector<std::string>     &object);
cq_ss_map_in   cq_cpp_ss_map_in  (const std::map<std::string, std::string> &);

std::vector<uint8_t>               cq_cpp_bytes_from   (cq_bytes_in    in);
std::vector<int64_t>               cq_cpp_i64_list_from(cq_i64_list_in in);
std::vector<std::string>           cq_cpp_str_list_from(cq_str_list_in in);
std::map<std::string, std::string> cq_cpp_ss_map_from  (cq_ss_map_in   in);

void cq_cpp_bytes_assign   (const std::vector<uint8_t>         &object, cq_bytes_out    out);
void cq_cpp_i64_list_assign(const std::vector<int64_t>         &object, cq_i64_list_out out);
void cq_cpp_str_list_assign(const std::vector<std::string>     &object, cq_str_list_out out);
void cq_cpp_ss_map_assign  (const std::map<std::string, std::string> &, cq_ss_map_out   out);

//object reference:

//create a cq_obj that references to $object.
//the return value need to release by cq_release_obj().
cq_obj *cq_retain_cpp_obj(cqObjectRef object, const std::string &cls);

//get the object that pointed by $obj.
//if $obj does not point a c++ object or that object is not a $cls, return null.
//it's equivalent to $cls is null and $cls is cqObject::clazz.
cqObjectRef cq_obj_raw_cpp(cq_obj *obj, cqClass *cls);

template<class T> typename cqRef<T>::Strong cq_obj_raw_cpp(cq_obj *obj) {
    return cqObject::cast<T>(cq_obj_raw_cpp(obj, T::clazz()));
}

_CQBASIS_END_VERSION_NS
