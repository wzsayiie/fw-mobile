#pragma once

#include "csscene.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

struct csSceneManager {
    
    static csSceneRef createScene(const std::string &name);
    static void loadScene(const std::string &name);
    static csSceneRef activeScene();
    
    static csGameObjectRef createGameObject(const std::string &name);
    static void dontDestoryOnLoad(csGameObjectRef gameObject);
    static void destroy(csGameObjectRef gameObject);
    
    static const std::map<void *, csGameObjectRef> &rootGameObjects(bool global);
};

_CSGAMEKIT_END_VERSION_NS
