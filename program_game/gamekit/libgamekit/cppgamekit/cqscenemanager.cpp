#include "cqscenemanager.hh"

static std::map<std::string, cqSceneRef> sAllScenes;
static cqSceneRef sActiveScene;

cqSceneRef cqSceneManager::createScene(const std::string &name) {
    if (name.empty()) {
        return nullptr;
    }
    if (sAllScenes.find(name) != sAllScenes.end()) {
        return nullptr;
    }
    
    cqSceneRef scene = cqScene::create();
    scene->setName(name);
    
    sAllScenes[name] = scene;
    return scene;
}

void cqSceneManager::loadScene(const std::string &name) {
    if (name.empty()) {
        return;
    }
    if (sAllScenes.find(name) == sAllScenes.end()) {
        return;
    }
    
    sActiveScene = sAllScenes[name];
}

cqSceneRef cqSceneManager::getActiveScene() {
    return sActiveScene;
}
