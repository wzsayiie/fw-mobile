#include "csscenemanager.hh"
#include "cqopengl.h"
#include "cqwnd.h"

//global data:

static std::map<std::string, csSceneRef> sAllScenes;
static csSceneRef sActiveScene;

static cq_wnd *sWnd = NULL;

//wnd:

static void load(cq_wnd *wnd) {
}

static void update(cq_wnd *wnd) {
    
    //NOTE: it's possibly to destroy game object in update(),
    //keep the traversed container unchanged.
    std::map<void *, csGameObjectRef> gameObjects;
    
    gameObjects = csGameObject::activeRoots();
    for (auto &cp : gameObjects) {
        cp.second->update();
    }
    
    gameObjects = csGameObject::globalRoots();
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
    if (sActiveScene && sActiveScene->name() == name) {
        return;
    }
    if (cqMap::dontContain(sAllScenes, name)) {
        return;
    }
    
    //remove old scene:
    csGameObject::destroyActiveRoots();
    
    //load new scene:
    sActiveScene = sAllScenes[name];
}

csSceneRef csSceneManager::activeScene() {
    return sActiveScene;
}
