#pragma once

#include "cqcppbasis.hh"

#include "CQUIKIT_NS.hh"
_CQUIKIT_BEGIN_NS

struct cqColor {
    
    float red;
    float blue;
    float green;
    float alpha;
    
    cqColor(float red, float blue, float green);
    cqColor(float red, float blue, float green, float alpha);
    
    static const cqColor blackColor;
    static const cqColor darkGrayColor;
    static const cqColor lightGrayColor;
    static const cqColor whiteColor;
    static const cqColor grayColor;
    static const cqColor redColor;
    static const cqColor greenColor;
    static const cqColor blueColor;
    static const cqColor cyanColor;
    static const cqColor yellowColor;
    static const cqColor magentaColor;
    static const cqColor orangeColor;
    static const cqColor purpleColor;
    static const cqColor brownColor;
    static const cqColor clearColor;
};

_CQUIKIT_END_NS
