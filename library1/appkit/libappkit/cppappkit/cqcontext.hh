#pragma once

#include "cqcolor.hh"
#include "cqgeometry.hh"

_CQAPPKIT_BEGIN_VERSION_NS

cq_class(cqContext, cqObject) {
    
    static void pushContext(cqContextRef context);
    static cqContextRef currentContext();
    static void popContext();
    
    virtual void setFillColor(cqColor color);
    
    virtual void fillRect(cqRect rect);
    virtual void fillEllipseInRect(cqRect rect);
    
    virtual void beginPath();
    virtual void moveToPoint(float x, float y);
    virtual void addLineToPoint(float x, float y);
    virtual void fillPath();
};

_CQAPPKIT_END_VERSION_NS
