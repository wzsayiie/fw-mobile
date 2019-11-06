#include "cqgeometry.hh"
#include <cstdarg>

static const char *makeString(const char *format, ...) {
    static thread_local char buffer[64];
    
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    return buffer;
}

//point:

cqPoint::cqPoint(): x(0), y(0) {
}

cqPoint::cqPoint(float x, float y): x(x), y(y) {
}

bool cqPoint::operator==(cqPoint that) const {
    return cq_flt_equal(x, that.x)
        && cq_flt_equal(y, that.y);
}

bool cqPoint::operator!=(cqPoint that) const {
    return !cq_flt_equal(x, that.x)
        || !cq_flt_equal(y, that.y);
}

const char *cqPoint::string() const {
    return makeString("(%.1f, %.1f)", x, y);
}

//size:

cqSize::cqSize(): width(0), height(0) {
}

cqSize::cqSize(float w, float h): width(w), height(h) {
}

bool cqSize::operator==(cqSize that) const {
    return cq_flt_equal(width , that.width )
        && cq_flt_equal(height, that.height);
}

bool cqSize::operator!=(cqSize that) const {
    return !cq_flt_equal(width , that.width )
        || !cq_flt_equal(height, that.height);
}

const char *cqSize::string() const {
    return makeString("(%.1f, %.1f)", width, height);
}

//rect:

cqRect::cqRect(): origin(0, 0), size(0, 0) {
}

cqRect::cqRect(float x, float y, float w, float h): origin(x, y), size(w, h) {
}

cqRect::cqRect(cqPoint orig, cqSize size): origin(orig), size(size) {
}

float cqRect::minX() const {return origin.x;}
float cqRect::minY() const {return origin.y;}
float cqRect::maxX() const {return origin.x + size.width ;}
float cqRect::maxY() const {return origin.y + size.height;}

bool cqRect::contains(cqPoint point) const {
    return minX() <= point.x && point.x < maxX()
        && minY() <= point.y && point.y < maxY();
}

bool cqRect::operator==(cqRect that) const {
    return origin == that.origin && size == that.size;
}

bool cqRect::operator!=(cqRect that) const {
    return origin != that.origin || size != that.size;
}

const char *cqRect::string() const {
    const char *f = "(%.1f, %.1f, %.1f, %.1f)";
    return makeString(f, origin.x, origin.y, size.width, size.height);
}
