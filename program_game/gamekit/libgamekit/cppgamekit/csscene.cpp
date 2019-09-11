#include "csscene.hh"
#include "cqopengl.h"
#include "cqwnd.h"

//global data:

static std::map<std::string, csSceneRef> sAllScenes;
static csSceneRef sActiveScene;

static std::map<void *, csGameObjectRef> sActiveGameObjects;
static std::map<void *, csGameObjectRef> sGlobalGameObjects;

static cq_wnd *sWnd = NULL;

//scene:

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

const std::map<void *, csGameObjectRef> &csScene::rootGameObject() {
    static std::map<void *, csGameObjectRef> empty;
    
    if (this == sActiveScene.get()) {
        return sActiveGameObjects;
    } else {
        return empty;
    }
}

//scene manager:

static void load(cq_wnd *wnd) {
}

static void gldraw(cq_wnd *wnd) {
    glClearColor(0.5, 0.6, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

static void initializeWindowNeeded() {
    if (sWnd != NULL) {
        return;
    }
    
    cq_wndproc proc = {nullptr};
    proc.load = load;
    proc.gldraw = gldraw;
    
    sWnd = cq_new_wnd();
    cq_set_wndproc(sWnd, &proc);
    cq_show_wnd(sWnd);
}

csSceneRef csSceneManager::createScene(const std::string &name) {
    if (name.empty()) {
        return nullptr;
    }
    if (cqMap::contains(sAllScenes, name)) {
        return nullptr;
    }
    
    initializeWindowNeeded();
    
    csSceneRef scene = csScene::createWithName(name);
    sAllScenes[name] = scene;
    return scene;
}

void csSceneManager::loadScene(const std::string &name) {
    if (name.empty()) {
        return;
    }
    if (cqMap::dontContain(sAllScenes, name)) {
        return;
    }
    
    sActiveScene = sAllScenes[name];
}

csSceneRef csSceneManager::getActiveScene() {
    return sActiveScene;
}

void csSceneManager::setRootGameObject(csGameObjectRef object, bool global) {
    if (object == nullptr) {
        return;
    }
    
    void *key = object.get();
    if (global) {
        sActiveGameObjects.erase(key);
        sGlobalGameObjects[key] = object;
    } else {
        sActiveGameObjects[key] = object;
        sGlobalGameObjects.erase(key);
    }
}

void csSceneManager::removeRootGameObject(csGameObjectRef object) {
    if (object == nullptr) {
        return;
    }
    
    void *key = object.get();
    sActiveGameObjects.erase(key);
    sGlobalGameObjects.erase(key);
}
