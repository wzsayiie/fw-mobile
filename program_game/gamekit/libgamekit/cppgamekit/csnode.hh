#pragma once

#include "csgamekitbase.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csNode, cqObject) {
    
    static void dontDestroyOnLoad(csNodeRef object);
    static void destroy(csNodeRef object);
};

_CSGAMEKIT_END_VERSION_NS
