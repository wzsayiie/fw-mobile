#include "gamelowroot.hh"

extern "C" void _cs_game_entry() {
    
    csSceneManager::createScene("LaunchScene");
    csSceneManager::loadScene("LaunchScene");
    
    auto rootObject = csGameObject::create("GameLowRoot");
    rootObject->addComponent(GameLowRoot::clazz());
}
