#include "cqgeometry.hh"

cqPoint::cqPoint()                 : x(0), y(0) {}
cqPoint::cqPoint(float x, float y) : x(x), y(x) {}

cqSize::cqSize()                 : width(0), height(0) {}
cqSize::cqSize(float w, float h) : width(w), height(h) {}

cqRect::cqRect()                                   : origin(0, 0), size(0, 0) {}
cqRect::cqRect(float x, float y, float w, float h) : origin(x, y), size(w, h) {}
cqRect::cqRect(cqPoint orig, cqSize size)          : origin(orig), size(size) {}

float cqRect::minX() const {return origin.x;}
float cqRect::minY() const {return origin.y;}
float cqRect::maxX() const {return origin.x + size.width ;}
float cqRect::maxY() const {return origin.y + size.height;}

bool cqRect::contains(cqPoint point) const {
    return minX() <= point.x < maxX()
    /**/&& minY() <= point.y < maxY();
}

static thread_local char _string_buffer[64];

const char *cqStringFromPoint(cqPoint p) {
    snprintf(_string_buffer, sizeof(_string_buffer), "(%.1f, %.1f)", p.x, p.y);
    return _string_buffer;
}

const char *cqStringFromSize(cqSize s) {
    snprintf(_string_buffer, sizeof(_string_buffer), "(%.1f, %.1f)", s.width, s.height);
    return _string_buffer;
}

const char *cqStringFromRect(cqRect r) {
    snprintf(_string_buffer, sizeof(_string_buffer),"(%.1f, %.1f, %.1f, %.1f)",
             r.origin.x  , r.origin.y,
             r.size.width, r.size.height);
    return _string_buffer;
}
