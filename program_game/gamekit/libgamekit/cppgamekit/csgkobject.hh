#pragma once

#include "csgamekitbase.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csGKObject, cqObject) {
    
    static void dontDestroyOnLoad(csGKObjectRef object);
    static void destroy(csGKObjectRef object);
};

_CSGAMEKIT_END_VERSION_NS
