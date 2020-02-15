#pragma once

#include "cscomponent.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csTransform, csComponent) {
    
    static std::vector<csTransformRef> activeRoots();
    static std::vector<csTransformRef> globalRoots();
    
    void handleCreate () override;
    void handleDestroy() override;
    
    //properties:
    virtual void setPosition(float x, float y);
    virtual float positionX();
    virtual float positionY();
    
    //hierarchy:
    virtual void asActiveRoot();
    virtual void asGlobalRoot();
    
    virtual void setParent(csTransformRef parent);
    virtual csTransformRef parent();
    virtual std::vector<csTransformRef> children();
    virtual void detachChildren();
};

_CSGAMEKIT_END_VERSION_NS
