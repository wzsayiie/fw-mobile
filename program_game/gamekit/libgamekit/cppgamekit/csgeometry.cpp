#include "csgeometry.hh"

static const char *makeString(const char *format, ...) {
    static thread_local char buffer[64];
    
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    return buffer;
}

//vector2:

csVector2::csVector2() {
    this->x = 0;
    this->y = 0;
}

csVector2::csVector2(float x, float y) {
    this->x = x;
    this->y = y;
}

bool csVector2::operator==(csVector2 that) const {
    return cq_flt_equal(x, that.x) && cq_flt_equal(y, that.y);
}

bool csVector2::operator!=(csVector2 that) const {
    return !cq_flt_equal(x, that.x) || !cq_flt_equal(y, that.y);
}

csVector2 csVector2::operator+(csVector2 that) const {
    return csVector2(x + that.x, y + that.y);
}

csVector2 csVector2::operator-(csVector2 that) const {
    return csVector2(x - that.x, y - that.y);
}

csVector2 csVector2::operator+=(csVector2 that) {
    x += that.x;
    y += that.y;
    return *this;
}

csVector2 csVector2::operator-=(csVector2 that) {
    x -= that.x;
    y -= that.y;
    return *this;
}

const char *csVector2::string() const {
    return makeString("(%.1f, %.1f)", x, y);
}

//rect:

csRect::csRect() {
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
}

csRect::csRect(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

csRect::csRect(csVector2 origin, csVector2 size) {
    this->x = origin.x;
    this->y = origin.y;
    this->width = size.x;
    this->height = size.y;
}

csVector2 csRect::center() const {
    return csVector2(x + width / 2, y + height / 2);
}

float csRect::xMin() const {return x;}
float csRect::yMin() const {return y;}
float csRect::xMax() const {return x + width ;}
float csRect::yMax() const {return y + height;}

bool csRect::contains(csVector2 p) const {
    return xMin() <= p.x && p.x < xMax() && yMin() <= p.y && p.y < yMax();
}

const char *csRect::string() const {
    return makeString("(%.1f, %.1f, %.1f, %.1f)", x, y, width, height);
}
