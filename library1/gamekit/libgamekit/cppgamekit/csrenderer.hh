#pragma once

#include "cscomponent.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csRenderer, csComponent) {
    
    static void renderAll();
    
    void handleCreate () override;
    void handleDestroy() override;
    
    virtual void handleRender();
};

_CSGAMEKIT_END_VERSION_NS
