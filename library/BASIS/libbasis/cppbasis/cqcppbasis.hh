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

#define cq_interface(SELF, SUPER) struct SELF : _cq_interface_middle<SELF, SUPER>

template<class SELF, class SUPER> struct _cq_interface_middle : SUPER {
    
    static_assert(sizeof(SUPER) == sizeof(void *),
        "interface shouldn't extend a class that contains data member");
    
    typedef shared_ptr<SELF> ref;
};

cq_interface(cqInterface, _cqRoot) {
};

//base class

#define cq_member(SELF)       struct SELF##_Data
#define cq_class(SELF, SUPER) struct SELF : _cq_class_middle<SELF, cq_member(SELF), SUPER>

template<class SELF, class DATA, class SUPER> struct _cq_class_middle : SUPER {

public:
    
    typedef shared_ptr<SELF> ref;
    
    template<class... A> static ref create(A... a) {
        return make_shared<SELF>(a...);
    }
    
protected:
    
    typedef SUPER super;
    
    shared_ptr<DATA> self;
    
    _cq_class_middle() : self(make_shared<DATA>()) {
    }
};

cq_class(cqObject, _cqRoot) {
    
    cqObject();
};
