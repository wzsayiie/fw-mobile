#include "csscenemanager.hh"
#include "cqopengl.h"
#include "cqwnd.h"
#include "csscript.hh"

//global data:

static std::map<std::string, csSceneRef> theAllScenes;
static csSceneRef theActiveScene;

static cq_wnd *theWnd = NULL;

//wnd:

static void load(cq_wnd *wnd) {
}

static void update(cq_wnd *wnd) {
    csScript::updateAllScripts();
}

static void gldraw(cq_wnd *wnd) {
    glClearColor(0.5, 0.6, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

static void initializeWndIfNeeded() {
    if (theWnd != NULL) {
        return;
    }
    
    cq_wndproc proc = {nullptr};
    proc.load = load;
    proc.update = update;
    proc.gldraw = gldraw;
    
    theWnd = cq_new_wnd();
    cq_set_wndproc(theWnd, &proc);
    cq_show_wnd(theWnd);
}

//scene manager:

csSceneRef csSceneManager::createScene(const std::string &name) {
    if (name.empty()) {
        return nullptr;
    }
    if (cqMap::contains(theAllScenes, name)) {
        return nullptr;
    }
    
    initializeWndIfNeeded();
    
    csSceneRef scene = csScene::create();
    scene->setNameIfNeeded(name);
    theAllScenes[name] = scene;
    return scene;
}

void csSceneManager::loadScene(const std::string &name) {
    if (name.empty()) {
        return;
    }
    if (theActiveScene && theActiveScene->name() == name) {
        return;
    }
    if (cqMap::dontContain(theAllScenes, name)) {
        return;
    }
    
    //remove old scene:
    for (csTransformRef transform : csTransform::activeRoots()) {
        csGameObject::destroy(transform->gameObject());
    }
    
    //load new scene:
    theActiveScene = theAllScenes[name];
}

csSceneRef csSceneManager::activeScene() {
    return theActiveScene;
}
