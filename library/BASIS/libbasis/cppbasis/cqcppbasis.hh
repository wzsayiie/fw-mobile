#pragma once

#include "cqcbasis.h"
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <set>
#include <vector>

struct cqClassInfo {
    cqClassInfo *const superclass;
    const char *const name;
};

inline cqClassInfo *_cqGetClassInfo(struct _cqObjectRoot *) {
    return nullptr;
}

struct _cqObjectRoot {
    std::weak_ptr<_cqObjectRoot> thisWeakRef;
    virtual cqClassInfo *dynamicSuperclass();
    virtual cqClassInfo *dynamicClass();
    virtual ~_cqObjectRoot();
};

#define _cq_ref(CLASS)     CLASS##Ref
#define _cq_weakref(CLASS) CLASS##WeakRef
#define _cq_dat(CLASS)     CLASS##Dat

#define cq_declare(CLASS)\
/**/    typedef std::shared_ptr<struct CLASS> _cq_ref(CLASS);\
/**/    typedef std::weak_ptr  <struct CLASS> _cq_weakref(CLASS);\
/**/    cqClassInfo *_cqGetClassInfo(struct CLASS *)

#define cq_member(CLASS)\
/**/    cqClassInfo *_cqGetClassInfo(struct CLASS *) {\
/**/        static cqClassInfo info = {\
/**/            CLASS::staticSuperclass(),\
/**/            ""#CLASS\
/**/        };\
/**/        return &info;\
/**/    }\
/**/    struct _cq_dat(CLASS)

#define cq_class(CLASS, SUPER)\
/**/    cq_declare(CLASS);\
/**/    struct CLASS : _cqSandWich<\
/**/        CLASS,\
/**/        _cq_ref(CLASS),\
/**/        _cq_weakref(CLASS),\
/**/        struct _cq_dat(CLASS),\
/**/        SUPER\
/**/    >

template<class CLASS, class REF, class WEAKREF, class DAT, class SUPER>
struct _cqSandWich : SUPER {

public:
    
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
    
    static cqClassInfo *staticSuperclass() {
        return _cqGetClassInfo((SUPER *)nullptr);
    }
    
    static cqClassInfo *staticClass() {
        return _cqGetClassInfo((CLASS *)nullptr);
    }
    
    cqClassInfo *dynamicSuperclass() override {
        return _cqGetClassInfo((SUPER *)nullptr);
    }
    
    cqClassInfo *dynamicClass() override {
        return _cqGetClassInfo((CLASS *)nullptr);
    }
    
    std::shared_ptr<DAT> dat;
    
protected:
    
    typedef SUPER super;
    
    _cqSandWich() : dat(std::make_shared<DAT>()) {
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
