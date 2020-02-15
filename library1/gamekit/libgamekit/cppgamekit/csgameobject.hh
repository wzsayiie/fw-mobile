#pragma once

#include "cstransform.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csGameObject, csNode) {
    
    //NOTE: new game object will be attached default components, and add to active scene.
    void init();
    void init(const std::string &name);
    
    static void destroy(csGameObjectRef gameObject);
    
    void handleCreate () override;
    void handleDestroy() override;
    
    //properites:
    virtual void setName(const std::string &name);
    virtual std::string name();
    
    //components:
    virtual csComponentRef addComponent(cqClass *clazz);
    virtual void removeComponent(csComponentRef component);
    
    template<class T> typename cqRef<T>::Strong addComponent() {
        return cqObject::cast<T>(addComponent(T::clazz()));
    }
    
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
