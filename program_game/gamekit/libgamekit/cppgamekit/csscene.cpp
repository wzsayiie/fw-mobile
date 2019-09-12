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

const std::vector<csGameObjectRef> &csScene::rootGameObject() {
    if (this == csSceneManager::getActiveScene().get()) {
        return csSceneManager::activeSceneVirtualRoot()->children();
    } else {
        static std::vector<csGameObjectRef> empty;
        return empty;
    }
}
