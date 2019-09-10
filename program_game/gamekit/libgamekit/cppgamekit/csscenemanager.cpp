#include "csscenemanager.hh"
#include "cqopengl.h"
#include "cqwnd.h"

static std::map<std::string, csSceneRef> sAllScenes;
static csSceneRef sActiveScene;
static cq_wnd *sWnd = NULL;

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
    if (sAllScenes.find(name) != sAllScenes.end()) {
        return nullptr;
    }
    
    initializeWindowNeeded();
    
    csSceneRef scene = csScene::create();
    scene->setName(name);
    
    sAllScenes[name] = scene;
    return scene;
}

void csSceneManager::loadScene(const std::string &name) {
    if (name.empty()) {
        return;
    }
    if (sAllScenes.find(name) == sAllScenes.end()) {
        return;
    }
    
    sActiveScene = sAllScenes[name];
}

csSceneRef csSceneManager::getActiveScene() {
    return sActiveScene;
}
