#pragma once

#include "cqcolor.hh"
#include "cqgeometry.hh"

_CQUIKIT_BEGIN_VERSION_NS

cq_declare(cqWindow);

struct cqContext {
    const float offsetX = 0;
    const float offsetY = 0;
    
    cqContext(float offsetX, float offsetY);
    void setFillColor(cqColor color);
    void fillRect(cqRect rect);
};

struct cqGraphics {
    
    static void startupGraphicsProgram(cqWindowRef window);
    static void prepareDraw();
    
    static void pushContext(cqContext context);
    static cqContext currentContext();
    static void popContext();
};

_CQUIKIT_END_VERSION_NS
