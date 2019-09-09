#pragma once

#include "csscene.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

struct csSceneManager {
    
    static csSceneRef createScene(const std::string &name);
    
    static void loadScene(const std::string &name);
    
    static csSceneRef getActiveScene();
};

_CSGAMEKIT_END_VERSION_NS
