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

//synchronization lock:

#define cq_synchronize(BLOCK)\
/**/    do {\
/**/        static std::mutex __cq_mutex;\
/**/        std::lock_guard<std::mutex> __cq_guard(__cq_mutex);\
/**/        BLOCK\
/**/    } while (0)

#define cq_synchronize_with(MUTEX, BLOCK)\
/**/    do {\
/**/        std::lock_guard<std::mutex> __cq_guard(MUTEX);\
/**/        BLOCK\
/**/    } while (0)

//class:

template<class T> struct cqRef {
    typedef std::shared_ptr<T> Strong;
    typedef std::weak_ptr<T> Weak;
};

struct cqClass;
struct _cqObjectRoot {
    cqRef<_cqObjectRoot>::Weak thisWeakRef;
    static  cqClass *getSuperclass();
    static  cqClass *getClass();
    virtual cqClass *superclass();
    virtual cqClass *clazz();
    virtual ~_cqObjectRoot();
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
    
    static typename cqRef<CLASS>::Strong create() {
        auto object = std::make_shared<CLASS>();
        object->thisWeakRef = object;
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
    
    static cqClass *getSuperclass() {
        return SUPER::getClass();
    }
    
    //the function implemented by macro cq_member()
    static cqClass *getClass();
    
    cqClass *superclass() override {
        return SUPER::getClass();
    }
    
    cqClass *clazz() override {
        return CLASS::getClass();
    }
};

struct cqObject;
struct cqClass {
    cqClass *const superclass;
    const char *const name;
    cqRef<cqObject>::Strong (*const create)();
};

template<class T> cqRef<cqObject>::Strong _cqObjectCreator() {
    return T::create();
}
template<class T> cqClass *_cqClassGet(const char *name) {
    static cqClass cls = {
        T::getSuperclass(),
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
/**/    template<> cqClass *_cqSandWich<CLASS, CLASS::super>::getClass() {\
/**/        return _cqClassGet<CLASS>(""#CLASS);\
/**/    }\
/**/    template<> struct _cqSandWich<CLASS, CLASS::super>::Dat

cq_class(cqObject, _cqObjectRoot) {
    
    virtual bool isKindOfClass(cqClass *cls);
    virtual bool isMemberOfClass(cqClass *cls);
    
    template<class T>
    auto cast() -> decltype(std::static_pointer_cast<T>(strongRef())) {
        return std::static_pointer_cast<T>(strongRef());
    }
};

//static object

template<class T, int = 0> typename cqRef<T>::Strong cqStaticObject() {
    cq_synchronize({
        static typename cqRef<T>::Strong object;
        if (object == nullptr) {
            object = T::create();
        }
        return object;
    });
}

_CQBASIS_END_VERSION_NS
