#pragma once

#include "cqresponder.hh"

struct cqPoint {
    float x;
    float y;
};

struct cqSize {
    float width;
    float height;
};

struct cqRect {
    cqPoint origin;
    cqSize size;
};

static const cqPoint cqPointZero = {0, 0};
static const cqSize  cqSizeZero  = {0, 0};
static const cqRect  cqRectZero  = {0, 0, 0, 0};

inline cqPoint cqPointMake(float x, float y) {cqPoint a = {x, y}; return a;}
inline cqSize  cqSizeMake (float w, float h) {cqSize  a = {w, h}; return a;}

inline cqRect cqRectMake(float x, float y, float w, float h) {
    cqRect a = {x, y, w, h};
    return a;
}

cq_class(cqView, cqResponder) {
    
    cqView();
    
    virtual cqView::ref hitTest(cqPoint point, cqEvent::ref event);
    virtual bool pointInside(cqPoint point, cqEvent::ref event);
};
