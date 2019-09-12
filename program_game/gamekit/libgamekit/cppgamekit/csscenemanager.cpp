#include "csscenemanager.hh"
#include "cqopengl.h"
#include "cqwnd.h"

//global data:

static std::map<std::string, csSceneRef> sAllScenes;
static csSceneRef sActiveScene;

static csGameObjectRef sActiveSceneVirtualRoot;
static csGameObjectRef sGlobalVirtualRoot;

static cq_wnd *sWnd = NULL;

//wnd:

static void load(cq_wnd *wnd) {
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

csSceneRef csSceneManager::getActiveScene() {
    return sActiveScene;
}

csGameObjectRef csSceneManager::activeSceneVirtualRoot() {
    if (sActiveSceneVirtualRoot == nullptr) {
        sActiveSceneVirtualRoot = csGameObject::create();
    }
    return sActiveSceneVirtualRoot;
}

csGameObjectRef csSceneManager::globalVirtualRoot() {
    if (sGlobalVirtualRoot == nullptr) {
        sGlobalVirtualRoot = csGameObject::create();
    }
    return sGlobalVirtualRoot;
}
