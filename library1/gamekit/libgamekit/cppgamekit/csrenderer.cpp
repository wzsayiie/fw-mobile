#include "csrenderer.hh"

cq_member(csRenderer) {
};

static void renderOne(float offsetX, float offsetY, csTransformRef transform) {
    auto renderers = transform->listComponents<csRenderer>();
    for (auto &it : renderers) {
        it->handleRender(offsetX, offsetY);
    }
    
    float childX = transform->positionX() + offsetX;
    float childY = transform->positionY() + offsetY;
    
    std::vector<csTransformRef> children = transform->children();
    for (auto &it : children) {
        renderOne(childX, childY, it);
    }
}

void csRenderer::renderAll(const std::vector<csTransformRef> &roots) {
    for (auto &it : roots) {
        renderOne(0, 0, it);
    }
}

void csRenderer::handleRender(float offsetX, float offsetY) {
}
