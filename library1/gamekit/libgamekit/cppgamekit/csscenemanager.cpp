#include "csscenemanager.hh"
#include "cqglkit.h"
#include "csrenderer.hh"
#include "csscript.hh"

//global data:

static std::map<std::string, csSceneRef> theAllScenes;
static csSceneRef theActiveScene;

static cq_wnd *theWnd = NULL;

//wnd:

static void load(cq_wnd *wnd) {
}

static void update(cq_wnd *wnd) {
    csScript::updateAll();
}

static void gldraw(cq_wnd *wnd) {
    
    float width  = cq_wnd_width (wnd);
    float height = cq_wnd_height(wnd);
    
    cq_begin_draw_fbo(width, height, CQ_SCREEN_FBO);
    cq_clear_current(1, 1, 1, 1);
    csRenderer::renderAll();
    cq_end_draw_fbo();
}

static void initializeWndIfNeeded() {
    if (theWnd != NULL) {
        return;
    }
    
    //NOTE: gl configuration.
    cq_set_coord_mode(cq_coord_mode_wld);
    cq_enable_alpha(true);
    
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
