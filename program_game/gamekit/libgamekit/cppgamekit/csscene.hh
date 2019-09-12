#pragma once

#include "csgameobject.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csScene, cqObject) {
    
    static csSceneRef createWithName(const std::string &name);
    
    virtual std::string name();
    virtual const std::map<void *, csGameObjectRef> &rootGameObjects();
};

_CSGAMEKIT_END_VERSION_NS
