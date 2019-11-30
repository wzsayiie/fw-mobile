#include "cqfont.hh"
#include "cqglkit.h"

cq_member(cqFont) {
    cq_font *font = nullptr;
};

static cq_ttf *sDefaultTTF = nullptr;
static std::map<float, cqFontRef> sDefaultFonts;

cqFontRef cqFont::systemFontOfSize(float size) {
    if (size <= 0) {
        return nullptr;
    }
    
    if (cqMap::contains(sDefaultFonts, size)) {
        return sDefaultFonts[size];
    }
    
    //load default true-type file.
    if (sDefaultTTF == nullptr) {
        sDefaultTTF = cq_new_ttf("");
    }
    
    //create font object.
    cqFontRef fontObject = cqFont::create();
    fontObject->dat->font = cq_new_font(sDefaultTTF, size);
    sDefaultFonts[size] = fontObject;
    
    //return.
    return fontObject;
}

float cqFont::pointSize() {
    return cq_font_size(dat->font);
}

void *cqFont::nativeFont() {
    return dat->font;
}
