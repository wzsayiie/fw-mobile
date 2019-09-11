#pragma once

#include "csgameobject.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csScene, cqObject) {
    
    static csSceneRef createWithName(const std::string &name);
    
    //properties:
    virtual std::string name();
    
    //root game object:
    virtual const std::map<void *, csGameObjectRef> &rootGameObject();
};

struct csSceneManager {
    
    static csSceneRef createScene(const std::string &name);
    static void loadScene(const std::string &name);
    static csSceneRef getActiveScene();
    
    virtual void setRootGameObject(csGameObjectRef object, bool global);
    virtual void removeRootGameObject(csGameObjectRef object);
};

_CSGAMEKIT_END_VERSION_NS
