#pragma once

#include "cqcbasis.h"
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

//root

struct _cqRoot {
    virtual ~_cqRoot() = default;
};

//base interface

#define cq_interface(SELF, SUPER) struct SELF : _cq_interface<SELF, SUPER>

template<class SELF, class SUPER> struct _cq_interface : SUPER {
    
    static_assert(sizeof(SUPER) == sizeof(void *),
        "interface shouldn't extend a class that contains data member");
    
    typedef shared_ptr<SELF> ref;
    
    template<class... A> static ref create(A... a) {
        return make_shared<SELF>(a...);
    }
};

cq_interface(cqInterface, _cqRoot) {
};

//base class

#define cq_class(SELF, DATA, SUPER) struct SELF : _cq_class<SELF, struct DATA, SUPER>

template<class SELF, class DATA, class SUPER> struct _cq_class : SUPER {
    
public:
    
    typedef shared_ptr<SELF> ref;
    
    template<class... A> static ref create(A... a) {
        return make_shared<SELF>(a...);
    }
    
protected:
    
    typedef SUPER super;
    
    shared_ptr<DATA> self;
    
    _cq_class() : self(make_shared<DATA>()) {
    }
};

cq_class(cqObject, _self_cqObject, _cqRoot) {
    
    cqObject();
};
