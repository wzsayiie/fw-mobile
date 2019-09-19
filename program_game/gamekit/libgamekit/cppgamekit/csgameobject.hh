#pragma once

#include "cstransform.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csGameObject, csGKObject) {
    
    //create and destroy:
    static const std::map<void *, csGameObjectRef> &activeRoots();
    static const std::map<void *, csGameObjectRef> &globalRoots();
    
    //NOTE: new game object will be attached default components, and add to active scene.
    static csGameObjectRef createWithName(const std::string &name);
    
    static void dontDestoryOnLoad(csGameObjectRef gameObject);
    static void destroyActiveRoots();
    static void destroy(csGameObjectRef gameObject);
    
    //properites:
    virtual void setName(const std::string &name);
    virtual std::string name();
    
    //hierarchy:
    virtual void setParent(csGameObjectRef parent);
    virtual csGameObjectRef parent();
    virtual const std::vector<csGameObjectRef> &children();
    virtual void detachChildren();
    
    //components:
    virtual void addComponent(cqClass *clazz);
    virtual void removeComponent(cqClass *clazz);
    virtual csComponentRef getComponent(cqClass *clazz);
    
    template<class T> typename cqRef<T>::Strong getComponent() {
        return cqObject::cast<T>(getComponent(T::clazz()));
    }
    
    virtual csTransformRef transform();
    
    //life cycle:
    virtual void update();
    virtual void onDestroy();
};

_CSGAMEKIT_END_VERSION_NS
