#include "csscene.hh"
#include "csscenemanager.hh"

cq_member(csScene) {
    std::string name;
};

csSceneRef csScene::createWithName(const std::string &name) {
    csSceneRef scene = csScene::create();
    scene->dat->name = name;
    return scene;
}

std::string csScene::name() {
    return dat->name;
}

const std::map<void *, csGameObjectRef> &csScene::rootGameObjects() {
    if (this == csSceneManager::activeScene().get()) {
        return csSceneManager::rootGameObjects(false);
    } else {
        static std::map<void *, csGameObjectRef> empty;
        return empty;
    }
}
