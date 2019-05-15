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
    
    typedef std::shared_ptr<SELF> ref;
};

cq_interface(cqInterface, _cqRoot) {
};

//object

#define cq_member(SELF)       struct SELF##_Data
#define cq_class(SELF, SUPER) struct SELF : _cq_class_middle<SELF, cq_member(SELF), SUPER>

template<class SELF, class DATA, class SUPER> struct _cq_class_middle : SUPER {

public:
    
    typedef std::weak_ptr<SELF> weak_ref;
    typedef std::shared_ptr<SELF> ref;
    
    template<class... A> static ref create(A... a) {
        auto object = std::make_shared<SELF>(a...);
        object->_weak = object;
        return object;
    }
    
    ref strong() const {
        return _weak.lock();
    }
    
    weak_ref weak() const {
        return _weak;
    }
    
protected:
    
    typedef SUPER super;
    
    std::shared_ptr<DATA> self;
    
    _cq_class_middle() : self(std::make_shared<DATA>()) {
    }
    
private:
    
    weak_ref _weak;
};

cq_class(cqObject, _cqRoot) {
    
    cqObject();
};
