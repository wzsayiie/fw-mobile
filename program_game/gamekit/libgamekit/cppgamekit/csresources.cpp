#include "csresources.hh"
#include "cqctool.hh"

static std::string sResourcesDirectory;

void csResources::setResourcesDirectory(const std::string &directory) {
    sResourcesDirectory = directory;
}

csTexture2DRef csResources::loadTexture2D(const std::string &path) {
    if (sResourcesDirectory.empty()) {
        return nullptr;
    }
    
    std::string file = cqPathString::append(sResourcesDirectory, path);
    return csTexture2D::create(file);
}

csSpriteRef csResources::loadSprite(const std::string &path) {
    if (sResourcesDirectory.empty()) {
        return nullptr;
    }
    
    std::string file = cqPathString::append(sResourcesDirectory, path);
    csTexture2DRef texture = csTexture2D::create(file);
    
    return csSprite::create(texture);
}
