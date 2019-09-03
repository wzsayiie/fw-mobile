#pragma once

#include "cqappkitbase.hh"

_CQAPPKIT_BEGIN_VERSION_NS

struct cqColor {
    
    float red   = 0;
    float green = 0;
    float blue  = 0;
    float alpha = 0;
    
    static cqColor iRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    static cqColor fRGBA(float r, float g, float b, float a);
    
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
