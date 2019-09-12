#include "csscenemanager.hh"
#include "cqopengl.h"
#include "cqwnd.h"

//global data:

static std::map<std::string, csSceneRef> sAllScenes;
static csSceneRef sActiveScene;

static std::map<void *, csGameObjectRef> sActiveObjects;
static std::map<void *, csGameObjectRef> sGlobalObjects;

static cq_wnd *sWnd = NULL;

//wnd:

static void load(cq_wnd *wnd) {
}

static void update(cq_wnd *wnd) {
    
    //NOTE: it's possibly to destroy game object in update(),
    //keep the traversed container unchanged.
    std::map<void *, csGameObjectRef> gameObjects;
    
    gameObjects = sActiveObjects;
    for (auto &cp : gameObjects) {
        cp.second->update();
    }
    
    gameObjects = sGlobalObjects;
    for (auto &cp : gameObjects) {
        cp.second->update();
    }
}

static void gldraw(cq_wnd *wnd) {
    glClearColor(0.5, 0.6, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

static void initializeWndIfNeeded() {
    if (sWnd != NULL) {
        return;
    }
    
    cq_wndproc proc = {nullptr};
    proc.load = load;
    proc.update = update;
    proc.gldraw = gldraw;
    
    sWnd = cq_new_wnd();
    cq_set_wndproc(sWnd, &proc);
    cq_show_wnd(sWnd);
}

//scene manager interfaces:

csSceneRef csSceneManager::createScene(const std::string &name) {
    if (name.empty()) {
        return nullptr;
    }
    if (cqMap::contains(sAllScenes, name)) {
        return nullptr;
    }
    
    initializeWndIfNeeded();
    
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

csSceneRef csSceneManager::activeScene() {
    return sActiveScene;
}

csGameObjectRef csSceneManager::createGameObject(const std::string &name) {
    csGameObjectRef gameObject = csGameObject::create();
    sActiveObjects[gameObject.get()] = gameObject;
    
    gameObject->setName(name);
    //NOTE: transform component is default.
    gameObject->addComponent(csTransform::getClass());
    
    return gameObject;
}

void csSceneManager::dontDestoryOnLoad(csGameObjectRef gameObject) {
    if (gameObject == nullptr) {
        return;
    }
    
    void *key = gameObject.get();
    if (cqMap::contains(sActiveObjects, key)) {
        sActiveObjects.erase(key);
    }
    if (cqMap::dontContain(sGlobalObjects, key)) {
        sGlobalObjects[key] = gameObject;
    }
}

void csSceneManager::destroy(csGameObjectRef gameObject) {
    if (gameObject == nullptr) {
        return;
    }
    
    void *key = gameObject.get();
    if (cqMap::contains(sActiveObjects, key)) {
        sActiveObjects[key]->onDestroy();
        sActiveObjects.erase(key);
    }
    if (cqMap::contains(sGlobalObjects, key)) {
        sGlobalObjects[key]->onDestroy();
        sGlobalObjects.erase(key);
    }
}

const std::map<void *, csGameObjectRef> &csSceneManager::rootGameObjects(bool global) {
    if (global) {
        return sGlobalObjects;
    } else {
        return sActiveObjects;
    }
}
