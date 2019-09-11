#pragma once

#include "csbaseobject.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_declare(csGameObject);

cq_class(csComponent, csBaseObject) {
    
    virtual void setGameObject(csGameObjectRef gameObject);
    virtual csGameObjectRef gameObject();
};

_CSGAMEKIT_END_VERSION_NS
