#include "csscenemanager.hh"
#include "csapplication.hh"

static std::map<std::string, csSceneRef> sAllScenes;
static csSceneRef sActiveScene;

csSceneRef csSceneManager::createScene(const std::string &name) {
    if (name.empty()) {
        return nullptr;
    }
    if (sAllScenes.find(name) != sAllScenes.end()) {
        return nullptr;
    }
    
    csApplication::initializeIfNeeded();
    
    csSceneRef scene = csScene::create();
    scene->setName(name);
    
    sAllScenes[name] = scene;
    return scene;
}

void csSceneManager::loadScene(const std::string &name) {
    if (name.empty()) {
        return;
    }
    if (sAllScenes.find(name) == sAllScenes.end()) {
        return;
    }
    
    sActiveScene = sAllScenes[name];
}

csSceneRef csSceneManager::getActiveScene() {
    return sActiveScene;
}
