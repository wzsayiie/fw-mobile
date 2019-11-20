#include "cqcontext.hh"
#include "cqglkit.h"
#include <cmath>

cq_member(cqContext) {
};

static std::vector<cqContextRef> sContextStack;

void cqContext::pushContext(cqContextRef context) {
    sContextStack.push_back(context);
}

cqContextRef cqContext::currentContext() {
    if (sContextStack.size() > 0) {
        return sContextStack.back();
    } else {
        return nullptr;
    }
}

void cqContext::popContext() {
    if (sContextStack.size() > 0) {
        sContextStack.pop_back();
    }
}

void cqContext::setFillColor(cqColor color) {
    cq_set_draw_color(color.red, color.green, color.blue, color.alpha);
}

void cqContext::fillRect(cqRect rect) {
    cq_draw_path_start_at(rect.minX(), rect.minY());
    cq_draw_path_add_at  (rect.maxX(), rect.minY());
    cq_draw_path_add_at  (rect.maxX(), rect.maxY());
    cq_draw_path_stop_at (rect.minX(), rect.maxY());
}

void cqContext::fillEllipseInRect(cqRect rect) {
    float xs = rect.size.width  / 2;
    float ys = rect.size.height / 2;
    float xc = rect.minX() + xs;
    float yc = rect.minY() + ys;
    
    auto s = 1.f / xs * ys;
    auto f = [s](float a, float b) {
        return sqrt(a * a - b * b) * s;
    };
    
    cq_draw_path_start();
    
    for (float i = xs; i > 0 ; i -= 1) cq_draw_path_add_at(xc - i, yc - f(xs, i));
    for (float i = 0 ; i < xs; i += 1) cq_draw_path_add_at(xc + i, yc - f(xs, i));
    for (float i = xs; i > 0 ; i -= 1) cq_draw_path_add_at(xc + i, yc + f(xs, i));
    for (float i = 0 ; i < xs; i += 1) cq_draw_path_add_at(xc - i, yc + f(xs, i));
    
    cq_draw_path_stop();
}

void cqContext::beginPath() {
}

void cqContext::moveToPoint(float x, float y) {
    cq_draw_path_start_at(x, y);
}

void cqContext::addLineToPoint(float x, float y) {
    cq_draw_path_add_at(x, y);
}

void cqContext::fillPath() {
    cq_draw_path_stop();
}
