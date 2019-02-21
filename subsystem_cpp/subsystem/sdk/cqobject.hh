#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <string>
#include <map>

using namespace std;

//root

struct _CQRoot {
    virtual ~_CQRoot() = default;
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

struct CQInterface : cq_interface<CQInterface, _CQRoot> {
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

struct CQObject : cq_class<CQObject, struct _self_CQObject, _CQRoot> {
    
    CQObject();
};
