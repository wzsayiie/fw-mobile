#include "csrenderer.hh"

cq_member(csRenderer) {
};

static std::set<csRendererRef> theRenderers;

void csRenderer::renderAll() {
    for (auto &it : theRenderers) {
        it->handleRender();
    }
}

void csRenderer::handleCreate() {
    super::handleCreate();
    
    theRenderers.insert(strongRef());
}

void csRenderer::handleDestroy() {
    super::handleDestroy();
    
    theRenderers.erase(strongRef());
}

void csRenderer::handleRender() {
}
