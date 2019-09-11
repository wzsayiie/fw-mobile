#pragma once

#include "cscomponent.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csGameObject, csBaseObject) {
    
    //NOTE: new object will be add to current active scene.
    static csGameObjectRef createWithName(const std::string &name);
    
    //properites:
    virtual void setName(const std::string &name);
    virtual std::string name();
    
    //hierarchy:
    virtual void setParent(csGameObjectRef parent);
    virtual const std::vector<csGameObjectRef> &children();
    
    //components:
    virtual void addComponent(cqClass *clazz);
    virtual void removeComponent(cqClass *clazz);
    virtual csComponentRef getComponent(cqClass *clazz);
};

_CSGAMEKIT_END_VERSION_NS
