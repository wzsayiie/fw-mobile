#pragma once

#include "cqcbasis.h"
#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <set>
#include <vector>

#include "CQCPPBASIS_NS.hh"
_CQCPPBASIS_BEGIN_NS

//std extension:

struct cqString {
    static std::string make(const char *value);
};

//thread mutex:

#define CQ_SYNCHRONIZE\
/**/    static std::mutex __cq_mutex;\
/**/    std::lock_guard<std::mutex> __cq_guard(__cq_mutex);

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

#define _cq_ref(CLASS)     CLASS##Ref
#define _cq_weakref(CLASS) CLASS##WeakRef

#define cq_declare(CLASS)\
/**/    typedef std::shared_ptr<struct CLASS> _cq_ref    (CLASS);\
/**/    typedef std::weak_ptr  <struct CLASS> _cq_weakref(CLASS);

#define cq_member(CLASS)\
/**/    template<> cqClassInfo *CLASS::_Sandwich::clazz(int) {\
/**/        static cqClassInfo info = {\
/**/            CLASS::superclass(0),\
/**/            ""#CLASS\
/**/        };\
/**/        return &info;\
/**/    }\
/**/    template<> struct CLASS::_Sandwich::_Dat

#define cq_class(CLASS, SUPER)\
/**/    cq_declare(CLASS);\
/**/    struct CLASS : _cqSandWich<\
/**/        CLASS,\
/**/        _cq_ref(CLASS),\
/**/        _cq_weakref(CLASS),\
/**/        SUPER\
/**/    >

template<class CLASS, class REF, class WEAKREF, class SUPER>
struct _cqSandWich : SUPER {

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
    
    static REF create() {
        auto object = std::make_shared<CLASS>();
        object->thisWeakRef = object;
        return object;
    }
    
    REF strongRef() const {
        auto ref = SUPER::thisWeakRef.lock();
        return std::static_pointer_cast<CLASS>(ref);
    }
    
    WEAKREF weakRef() const {
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

cq_class(cqObject, _cqObjectRoot) {
    
    cqObject();
    
    virtual bool isKindOfClass(cqClassInfo *info);
    virtual bool isMemberOfClass(cqClassInfo *info);
    
    template<class T>
    auto cast() -> decltype(std::static_pointer_cast<T>(strongRef())) {
        return std::static_pointer_cast<T>(strongRef());
    }
};

_CQCPPBASIS_END_NS
