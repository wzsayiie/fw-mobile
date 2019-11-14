#pragma once

#include "csgamekitbase.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csNode, cqObject) {
    
    virtual void handleCreate ();
    virtual void handleDestroy();
    
    static void dontDestroyOnLoad(csNodeRef node);
    static void destroy(csNodeRef node);
};

_CSGAMEKIT_END_VERSION_NS
