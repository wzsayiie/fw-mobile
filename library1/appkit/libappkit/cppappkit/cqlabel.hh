#pragma once

#include "cqfont.hh"
#include "cqview.hh"

_CQAPPKIT_BEGIN_VERSION_NS

cq_class(cqLabel, cqView) {
    
    void init();
    void init(cqRect frame);
    
    virtual void setText(const std::string &text);
    virtual std::string text();
    
    virtual void setTextColor(cqColor color);
    virtual cqColor textColor();
    
    virtual void setFont(cqFontRef font);
    virtual cqFontRef font();
    
    void drawRect(cqRect rect) override;
};

_CQAPPKIT_END_VERSION_NS
