#pragma once

#include "cqappkitbase.hh"

_CQAPPKIT_BEGIN_VERSION_NS

struct cqPoint {
    
    float x;
    float y;
    
    cqPoint();
    cqPoint(float x, float y);
    
    bool operator==(cqPoint that) const;
    bool operator!=(cqPoint that) const;
    
    cqPoint operator+(cqPoint that) const;
    cqPoint operator-(cqPoint that) const;
    
    cqPoint operator+=(cqPoint that);
    cqPoint operator-=(cqPoint that);
    
    const char *string() const;
};

struct cqSize {
    
    float width;
    float height;
    
    cqSize();
    cqSize(float width, float height);
    
    bool operator==(cqSize that) const;
    bool operator!=(cqSize that) const;
    
    const char *string() const;
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
    
    bool operator==(cqRect that) const;
    bool operator!=(cqRect that) const;
    
    const char *string() const;
};

_CQAPPKIT_END_VERSION_NS
