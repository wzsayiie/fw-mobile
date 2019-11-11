#pragma once

#include "csgamekitbase.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

struct csVector2 {
    
    float x;
    float y;
    
    csVector2();
    csVector2(float x, float y);
    
    bool operator==(csVector2 that) const;
    bool operator!=(csVector2 that) const;
    
    csVector2 operator+(csVector2 that) const;
    csVector2 operator-(csVector2 that) const;
    
    csVector2 operator+=(csVector2 that);
    csVector2 operator-=(csVector2 that);
    
    const char *string() const;
};

struct csRect {
    
    float x;
    float y;
    float width;
    float height;
    
    csRect();
    csRect(float x, float y, float width, float height);
    csRect(csVector2 origin, csVector2 size);
    
    csVector2 center() const;
    
    float xMin() const;
    float yMin() const;
    float xMax() const;
    float yMax() const;
    
    bool contains(csVector2 point) const;
    
    const char *string() const;
};

_CSGAMEKIT_END_VERSION_NS
