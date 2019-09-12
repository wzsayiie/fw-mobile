#pragma once

#include "csbaseobject.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_declare(csGameObject);
cq_declare(csTransform);

cq_class(csComponent, csBaseObject) {
    
    //csGameObject.addComponent() will invoke this function, developer should not call it.
    virtual void resetGameObjectIfNeeded(csGameObjectRef gameObject);
    
    virtual csGameObjectRef gameObject();
    
    //get brother components:
    virtual csComponentRef getComponent(cqClass *clazz);
    
    template<class T>
    auto getComponent() -> decltype(cqObject::cast<T>(getComponent(nullptr))) {
        return cqObject::cast<T>(getComponent(T::getClass()));
    }
    
    virtual csTransformRef transform();
    
    //life cycle:
    virtual void awake();
    virtual void start();
    virtual void update();
    virtual void onDestroy();
};

_CSGAMEKIT_END_VERSION_NS
