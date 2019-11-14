#include "csscene.hh"
#include "csgameobject.hh"
#include "csscenemanager.hh"

cq_member(csScene) {
    std::string name;
};

void csScene::setNameIfNeeded(const std::string &name) {
    if (dat->name.empty()) {
        dat->name = name;
    }
}

std::string csScene::name() {
    return dat->name;
}

std::vector<csGameObjectRef> csScene::rootGameObjects() {
    std::vector<csGameObjectRef> gameObjects;
    if (this == csSceneManager::activeScene().get()) {
        for (csTransformRef transform : csTransform::activeRoots()) {
            gameObjects.push_back(transform->gameObject());
        }
    }
    return gameObjects;
}
