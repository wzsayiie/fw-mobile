#include "gameroot.hh"

extern "C" void _cq_game_entry() {
    
    cqSceneManager::createScene("LaunchScene");
    cqSceneManager::loadScene("LaunchScene");
    
    cqGameObjectRef gameRootObject = cqGameObject::createGameObject();
    gameRootObject->addComponent(GameRoot::create());
}
