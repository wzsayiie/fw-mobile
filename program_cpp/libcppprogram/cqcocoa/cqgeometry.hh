#pragma once

#include "cqcocoabase.hh"

_CQCOCOA_BEGIN_VERSION_NS

struct cqPoint {
    
    float x;
    float y;
    
    cqPoint();
    cqPoint(float x, float y);
};

struct cqSize {
    
    float width;
    float height;
    
    cqSize();
    cqSize(float width, float height);
};

struct cqRect {
    
    cqPoint origin;
    cqSize size;
    
    cqRect();
    cqRect(float x, float y, float width, float height);
    cqRect(cqPoint origin, cqSize size);
    
    float minX() const;
    float minY() const;
    float maxX() const;
    float maxY() const;
    
    bool contains(cqPoint point) const;
};

const char *cqStringFromPoint(cqPoint point);
const char *cqStringFromSize(cqSize size);
const char *cqStringFromRect(cqRect rect);

_CQCOCOA_END_VERSION_NS
