#pragma once

#include "csgamekitbase.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csBaseObject, cqObject) {
    
    //when a new scene loaded, do not detach $object from game object tree.
    //$object should be a csGameObject or csComponent.
    static void dontDetachOnLoad(csBaseObjectRef object);
    
    //detach $object from game object tree.
    //$object should be a csGameObject or csComponent.
    static void detach(csBaseObjectRef object);
};

_CSGAMEKIT_END_VERSION_NS
