#include "cqattributedstring.hh"
#include "cqglkit.h"

cqSize cqAttributedString::sizeWithAttributes(const std::string &s, cqStringAttributes a) {
    if (s.empty()) {
        return cqSize();
    }
    if (a.font == nullptr) {
        return cqSize();
    }
    
    auto  font   = (cq_font *)a.font->nativeFont();
    float width  = cq_drawing_str_wide(font, s.c_str());
    float height = cq_font_size(font);
    
    return cqSize(width, height);
}

void cqAttributedString::drawAtPoint(cqPoint p, const std::string &s, cqStringAttributes a) {
    if (s.empty()) {
        return;
    }
    if (a.font == nullptr) {
        return;
    }
    
    auto color = a.foregroundColor;
    cq_set_draw_color(color.red, color.green, color.blue, color.alpha);
    
    auto font = (cq_font *)a.font->nativeFont();
    cq_draw_str(p.x, p.y, font, s.c_str());
}
