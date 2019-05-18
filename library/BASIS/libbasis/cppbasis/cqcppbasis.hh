#pragma once

#include "cqcbasis.h"
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <set>
#include <vector>

#define _cq_ref(CLASS)     CLASS##Ref
#define _cq_weakref(CLASS) CLASS##WeakRef

#define _cq_declare_ref(CLASS)     typedef std::shared_ptr<struct CLASS> _cq_ref(CLASS)
#define _cq_declare_weakref(CLASS) typedef std::weak_ptr  <struct CLASS> _cq_weakref(CLASS)

#define cq_declare(CLASS) _cq_declare_ref(CLASS);_cq_declare_weakref(CLASS)

struct _cqObjectRoot {
    std::weak_ptr<_cqObjectRoot> thisWeakRef;
    virtual ~_cqObjectRoot() {}
};

#define cq_member(CLASS) struct CLASS##Dat

#define cq_class(C, S) cq_declare(C); struct C : _cqM<C, _cq_ref(C), _cq_weakref(C), cq_member(C), S>

template<class CLASS, class REF, class WEAKREF, class DAT, class SUPER> struct _cqM : SUPER {

public:
    
    template<class... A> static REF create(A... a) {
        auto object = std::make_shared<CLASS>(a...);
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
    
    std::shared_ptr<DAT> dat;
    
protected:
    
    typedef SUPER super;
    
    _cqM() : dat(std::make_shared<DAT>()) {
    }
};

cq_class(cqObject, _cqObjectRoot) {
    cqObject();
};
