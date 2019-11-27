#pragma once

#include "cqcolor.hh"
#include "cqfont.hh"
#include "cqgeometry.hh"

_CQAPPKIT_BEGIN_VERSION_NS

struct cqStringAttributes {
    cqFontRef font;
    cqColor foregroundColor;
};

struct cqAttributedString {
    
    static cqSize sizeWithAttributes(const std::string &s, cqStringAttributes a);
    
    static void drawAtPoint(cqPoint p, const std::string &s, cqStringAttributes a);
};

_CQAPPKIT_END_VERSION_NS
