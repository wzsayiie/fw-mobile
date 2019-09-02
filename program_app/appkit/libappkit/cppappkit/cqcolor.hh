#pragma once

#include "cqappkitbase.hh"

_CQAPPKIT_BEGIN_VERSION_NS

struct cqColor {
    
    float red;
    float blue;
    float green;
    float alpha;
    
    cqColor();
    cqColor(float red, float blue, float green);
    cqColor(float red, float blue, float green, float alpha);
    
    static const cqColor BlackColor;
    static const cqColor DarkGrayColor;
    static const cqColor LightGrayColor;
    static const cqColor WhiteColor;
    static const cqColor GrayColor;
    static const cqColor RedColor;
    static const cqColor GreenColor;
    static const cqColor BlueColor;
    static const cqColor CyanColor;
    static const cqColor YellowColor;
    static const cqColor MagentaColor;
    static const cqColor OrangeColor;
    static const cqColor PurpleColor;
    static const cqColor BrownColor;
    static const cqColor ClearColor;
};

_CQAPPKIT_END_VERSION_NS
