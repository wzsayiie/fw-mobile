#pragma once

#include "cqctoolbase.hh"

_CQCTOOL_BEGIN_VERSION_NS

cq_class(cqDispatchQueue, cqObject) {
    
    //a cqDispatchQueue object can be called on different threads.
    
    virtual void post(std::function<void ()> task);
    virtual bool empty();
    virtual void update();
};

struct cqDispatch {
    
    static void asyncOnGlobal(std::function<void ()> task);
    static void asyncOnMain(std::function<void ()> task);

    //if userControlEnabled(default false) is true, user need calling updateMain() manually.
    static void setUserControlEnabled(bool enabled);
    
    static bool mainQueueEmpty();
    static void updateMain();
};

_CQCTOOL_END_VERSION_NS
