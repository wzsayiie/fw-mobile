#pragma once

#include "csgameobject.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csScene, cqObject) {
    
    virtual void setNameIfNeeded(const std::string &name);
    virtual std::string name();
    
    virtual std::vector<csGameObjectRef> rootGameObjects();
};

_CSGAMEKIT_END_VERSION_NS
