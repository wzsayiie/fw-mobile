#pragma once

#include "csgameobject.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csScene, cqObject) {
    
    static csSceneRef createWithName(const std::string &name);
    
    virtual std::string name();
    virtual const std::vector<csGameObjectRef> &rootGameObject();
};

_CSGAMEKIT_END_VERSION_NS
