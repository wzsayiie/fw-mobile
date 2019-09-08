#pragma once

#include "cqscene.hh"

_CQGAMEKIT_BEGIN_VERSION_NS

struct cqSceneManager {
    
    static cqSceneRef createScene(const std::string &name);
    
    static void loadScene(const std::string &name);
    
    static cqSceneRef getActiveScene();
};

_CQGAMEKIT_END_VERSION_NS
