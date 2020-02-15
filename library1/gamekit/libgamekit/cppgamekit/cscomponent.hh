#pragma once

#include "csnode.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_declare(csGameObject);
cq_declare(csTransform);

cq_class(csComponent, csNode) {
    
    //properties:
    virtual void setGameObjectIfNeeded(csGameObjectRef gameObject);
    virtual csGameObjectRef gameObject();
    
    //get brother components:
    virtual std::vector<csComponentRef> listComponents(cqClass *clazz);
    virtual csComponentRef getComponent(cqClass *clazz);
    
    template<class T>
    typename std::vector<typename cqRef<T>::Strong> listComponents() {
        typename std::vector<typename cqRef<T>::Strong> vector;
        for (csComponentRef it : listComponents(T::clazz())) {
            vector.push_back(cqObject::cast<T>(it));
        }
        return vector;
    }
    
    template<class T>
    typename cqRef<T>::Strong getComponent() {
        return cqObject::cast<T>(getComponent(T::clazz()));
    }
    
    virtual csTransformRef transform();
};

_CSGAMEKIT_END_VERSION_NS
