#pragma once

#include "cqgamekitbase.hh"

_CQGAMEKIT_BEGIN_VERSION_NS

cq_class(cqGKObject, cqObject) {
    
    static void dontDestroyOnLoad(cqGKObjectRef object);
};

_CQGAMEKIT_END_VERSION_NS
