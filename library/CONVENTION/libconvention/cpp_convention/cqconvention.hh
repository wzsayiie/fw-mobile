#pragma once

#include "cq_convention.h"
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

template<class SELF, class SUPER> struct cq_interface : SUPER {
    
    static_assert(sizeof(SUPER) == sizeof(void *),
        "interface shouldn't extend a class that contains data member");
    
    typedef shared_ptr<SELF> ref;
    
    template<class... A> static ref create(A... a) {
        return make_shared<SELF>(a...);
    }
};

struct cqInterface : cq_interface<cqInterface, _cqRoot> {
};

//base class

template<class SELF, class DATA_STRUCT, class SUPER> struct cq_class : SUPER {
    
public:
    
    typedef shared_ptr<SELF> ref;
    
    template<class... A> static ref create(A... a) {
        return make_shared<SELF>(a...);
    }
    
protected:
    
    typedef SUPER super;
    
    shared_ptr<DATA_STRUCT> self;
    
    cq_class() : self(make_shared<DATA_STRUCT>()) {
    }
};

struct cqObject : cq_class<cqObject, struct _self_cqObject, _cqRoot> {
    
    cqObject();
};
