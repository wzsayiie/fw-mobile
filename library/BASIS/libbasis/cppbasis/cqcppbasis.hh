#pragma once

#include "cqcbasis.h"
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <set>
#include <vector>

struct _cqRoot {
    virtual ~_cqRoot() = default;
};

//interface

#define cq_interface(SELF, SUPER) struct SELF : _cq_interface_middle<SELF, SUPER>

template<class SELF, class SUPER> struct _cq_interface_middle : SUPER {
    
    static_assert(sizeof(SUPER) == sizeof(void *),
        "interface shouldn't extend a class that contains data member");
    
    typedef std::shared_ptr<SELF> Ref;
};

cq_interface(cqInterface, _cqRoot) {
};

//object

#define cq_member(SELF)       struct SELF##_Data
#define cq_class(SELF, SUPER) struct SELF : _cq_class_middle<SELF, cq_member(SELF), SUPER>

template<class SELF, class DATA, class SUPER> struct _cq_class_middle : SUPER {

public:
    
    typedef std::weak_ptr<SELF> WeakRef;
    typedef std::shared_ptr<SELF> Ref;
    
    template<class... A> static Ref create(A... a) {
        auto object = std::make_shared<SELF>(a...);
        object->thisWeakRef = object;
        return object;
    }
    
    Ref strongRef() const {
        auto ref = SUPER::thisWeakRef.lock();
        return std::static_pointer_cast<SELF>(ref);
    }
    
    WeakRef weakRef() const {
        auto ref = SUPER::thisWeakRef.lock();
        return std::static_pointer_cast<SELF>(ref);
    }
    
    std::shared_ptr<DATA> dat;
    
protected:
    
    typedef SUPER super;
    
    _cq_class_middle() : dat(std::make_shared<DATA>()) {
    }
};

struct _cqObjectRoot : _cqRoot {
    std::weak_ptr<_cqObjectRoot> thisWeakRef;
};

cq_class(cqObject, _cqObjectRoot) {
    cqObject();
};
