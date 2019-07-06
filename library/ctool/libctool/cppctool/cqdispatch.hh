#pragma once

#include "cqcppbasis.hh"

#include "CQCTOOL_NS.hh"
_CQCTOOL_BEGIN_NS

cq_class(cqDispatchQueue, cqObject) {
    
    //a cqDispatchQueue object can be called on different threads.
    
    cqDispatchQueue();
    
    virtual void post(std::function<void ()> task);
    
    virtual bool empty();
    
    virtual void update();
};

struct cqDispatch {
    
    static void asyncOnGlobal(std::function<void ()> task);

    static void asyncOnMain(std::function<void ()> task);

    static void updateMain();
};

_CQCTOOL_END_NS
