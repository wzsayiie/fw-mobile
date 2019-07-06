#pragma once

#include "cqcbasis.h"

#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <atomic>
#include <mutex>

#include <algorithm>

#include "CQCPPBASIS_NS.hh"
_CQCPPBASIS_BEGIN_NS

//std extension:

struct cqString {
    static std::string make(const char *value);
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

struct cqClassInfo {
    cqClassInfo *const superclass;
    const char *const name;
};

struct _cqObjectRoot {
    std::weak_ptr<_cqObjectRoot> thisWeakRef;
    static  cqClassInfo *superclass(int);
    static  cqClassInfo *clazz(int);
    virtual cqClassInfo *superclass();
    virtual cqClassInfo *clazz();
    virtual ~_cqObjectRoot();
};

template<class T> struct cqRef {
    typedef std::shared_ptr<T> Strong;
    typedef std::weak_ptr<T> Weak;
};

#define cq_declare(CLASS)\
/**/    struct CLASS;\
/**/    typedef cqRef<CLASS>::Strong CLASS##Ref;\
/**/    typedef cqRef<CLASS>::Weak CLASS##WeakRef;

#define cq_class(CLASS, SUPER)\
/**/    cq_declare(CLASS)\
/**/    struct CLASS : _cqSandWich<CLASS, SUPER>

template<class CLASS, class SUPER> struct _cqSandWich : SUPER {

private:

    typedef _cqSandWich _Sandwich;
    
    //the struct implemented by macro cq_member()
    struct _Dat;

protected:

    typedef SUPER super;

    _cqSandWich() : dat(std::make_shared<_Dat>()) {
    }

public:
    
    std::shared_ptr<_Dat> dat;
    
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
    
    static cqClassInfo *superclass(int) {
        return SUPER::clazz(0);
    }
    
    //the function implemented by macro cq_member()
    static cqClassInfo *clazz(int);
    
    cqClassInfo *superclass() override {
        return SUPER::clazz(0);
    }
    
    cqClassInfo *clazz() override {
        return CLASS::clazz(0);
    }
};

template<class T> cqClassInfo *_cqClassInfoGet(const char *name) {
    static cqClassInfo info = {
        T::superclass(0),
        name
    };
    return &info;
}

#define cq_member(CLASS)\
/**/    template<> cqClassInfo *CLASS::_Sandwich::clazz(int) {\
/**/        return _cqClassInfoGet<CLASS>(""#CLASS);\
/**/    }\
/**/    template<> struct CLASS::_Sandwich::_Dat

cq_class(cqObject, _cqObjectRoot) {
    
    cqObject();
    
    virtual bool isKindOfClass(cqClassInfo *info);
    virtual bool isMemberOfClass(cqClassInfo *info);
    
    template<class T>
    auto cast() -> decltype(std::static_pointer_cast<T>(strongRef())) {
        return std::static_pointer_cast<T>(strongRef());
    }
};

//shared object

template<class T, int = 0> typename cqRef<T>::Strong cqStaticObject() {
    cq_synchronize({
        static typename cqRef<T>::Strong object;
        if (object == nullptr) {
            object = T::create();
        }
        return object;
    });
}

_CQCPPBASIS_END_NS
