#pragma once

#include "csgamekitbase.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csBaseObject, cqObject) {
    
    static void dontDestroyOnLoad(csBaseObjectRef object);
};

_CSGAMEKIT_END_VERSION_NS
