#include "gameroot.hh"

extern "C" void _cs_game_entry() {
    
    csSceneManager::createScene("LaunchScene");
    csSceneManager::loadScene("LaunchScene");
    
    csGameObjectRef gameRootObject = csGameObject::createGameObject();
    gameRootObject->addComponent(GameRoot::create());
}
