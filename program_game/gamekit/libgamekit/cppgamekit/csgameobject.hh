#pragma once

#include "cstransform.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csGameObject, csBaseObject) {
    
    //NOTE: new object will be added default components,
    //and attached to current active scene.
    static csGameObjectRef createWithName(const std::string &name);
    
    //properites:
    virtual void setName(const std::string &name);
    virtual std::string name();
    
    //hierarchy:
    virtual void setParent(csGameObjectRef parent);
    virtual csGameObjectRef parent();
    virtual const std::vector<csGameObjectRef> &children();
    
    //components:
    virtual void addComponent(cqClass *clazz);
    virtual void removeComponent(cqClass *clazz);
    virtual csComponentRef getComponent(cqClass *clazz);
    
    template<class T>
    auto getComponent() -> decltype(cqObject::cast<T>(getComponent(nullptr))) {
        return cqObject::cast<T>(getComponent(T::getClass()));
    }
    
    virtual csTransformRef transform();
};

_CSGAMEKIT_END_VERSION_NS
