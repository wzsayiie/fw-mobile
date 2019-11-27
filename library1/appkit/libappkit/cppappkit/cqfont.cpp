#include "cqfont.hh"
#include "cqglkit.h"

cq_member(cqFont) {
    cq_font *font;
};

cqFontRef cqFont::systemFontOfSize(float size) {
    return cqStaticObject<cqFont>();
}

void *cqFont::nativeFont() {
    return dat->font;
}
