#include "cqlabel.hh"
#include "cqattributedstring.hh"

cq_member(cqLabel) {
    std::string text;
    cqColor textColor;
    cqFontRef font;
};

void cqLabel::init() {
    init(cqRect());
}

void cqLabel::init(cqRect frame) {
    super::init(frame);
    
    setBackgroundColor(cqColor::ClearColor);
}

void cqLabel::setText(const std::string &text) {
    dat->text = text;
}

std::string cqLabel::text() {
    return dat->text;
}

void cqLabel::setTextColor(cqColor color) {
    dat->textColor = color;
}

cqColor cqLabel::textColor() {
    return dat->textColor;
}

void cqLabel::setFont(cqFontRef font) {
    dat->font = font;
}

cqFontRef cqLabel::font() {
    return dat->font;
}

void cqLabel::drawRect(cqRect rect) {
    
    cqFontRef font = dat->font;
    if (font == nullptr) {
        font = cqFont::systemFontOfSize(12);
    }
    
    cqColor textColor = dat->textColor;
    if (textColor == cqColor::ClearColor) {
        textColor = cqColor::BlackColor;
    }
    
    //calculate text's size.
    cqStringAttributes attributes;
    attributes.font = font;
    attributes.foregroundColor = textColor;
    
    cqSize textSize = cqAttributedString::sizeWithAttributes(dat->text, attributes);
    
    //draw text.
    cqPoint origin;
    origin.x = (rect.size.width  - textSize.width ) / 2;
    origin.y = (rect.size.height - textSize.height) / 2;
    
    cqAttributedString::drawAtPoint(origin, dat->text, attributes);
}
