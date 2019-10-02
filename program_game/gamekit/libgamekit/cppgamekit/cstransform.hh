#pragma once

#include "cscomponent.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

struct csVector3 {
    
    float x;
    float y;
    float z;
    
    csVector3();
    csVector3(float x, float y, float z);
};

cq_class(csTransform, csComponent) {
    
    static std::vector<csTransformRef> activeRoots();
    static std::vector<csTransformRef> globalRoots();
    
    void handleCreate () override;
    void handleDestroy() override;
    
    //properties:
    virtual void setPosition(csVector3 position);
    virtual csVector3 position();
    
    //hierarchy:
    virtual void asActiveRoot();
    virtual void asGlobalRoot();
    
    virtual void setParent(csTransformRef parent);
    virtual csTransformRef parent();
    virtual std::vector<csTransformRef> children();
    virtual void detachChildren();
};

_CSGAMEKIT_END_VERSION_NS
