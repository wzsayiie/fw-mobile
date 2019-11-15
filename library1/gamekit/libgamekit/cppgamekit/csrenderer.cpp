#include "csrenderer.hh"

cq_member(csRenderer) {
};

static void renderOne(csVector2 offset, csTransformRef transform) {
    auto renderers = transform->getComponents<csRenderer>();
    for (auto &it : renderers) {
        it->handleRender(offset);
    }
    
    auto childOffset = transform->position() + offset;
    auto children = transform->children();
    for (auto &it : children) {
        renderOne(childOffset, it);
    }
}

void csRenderer::renderAll(const std::vector<csTransformRef> &roots) {
    for (auto &it : roots) {
        renderOne(csVector2(), it);
    }
}

void csRenderer::handleRender(csVector2 offset) {
}
