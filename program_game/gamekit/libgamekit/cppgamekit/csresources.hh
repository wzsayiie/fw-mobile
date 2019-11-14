#pragma once

#include "csgamekitbase.hh"
#include "cssprite.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

struct csResources {
    
    static void setResourcesDirectory(const std::string &directory);
    
    static csTexture2DRef loadTexture2D(const std::string &path);
    static csSpriteRef loadSprite(const std::string &path);
};

_CSGAMEKIT_END_VERSION_NS
