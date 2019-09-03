#include "cqcolor.hh"

cqColor cqColor::iRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    cqColor color;
    
    color.red   = r / 255.f;
    color.green = g / 255.f;
    color.blue  = b / 255.f;
    color.alpha = a / 255.f;
    
    return color;
}

cqColor cqColor::fRGBA(float r, float g, float b, float a) {
    cqColor color;
    
    color.red   = r;
    color.green = g;
    color.blue  = b;
    color.alpha = a;
    
    return color;
}

const cqColor cqColor::BlackColor     = cqColor::fRGBA(0.0f, 0.0f, 0.0f, 1.f);
const cqColor cqColor::DarkGrayColor  = cqColor::fRGBA(0.3f, 0.3f, 0.3f, 1.f);
const cqColor cqColor::LightGrayColor = cqColor::fRGBA(0.6f, 0.6f, 0.6f, 1.f);
const cqColor cqColor::WhiteColor     = cqColor::fRGBA(1.0f, 1.0f, 1.0f, 1.f);
const cqColor cqColor::GrayColor      = cqColor::fRGBA(0.5f, 0.5f, 0.5f, 1.f);
const cqColor cqColor::RedColor       = cqColor::fRGBA(1.0f, 0.4f, 0.4f, 1.f);
const cqColor cqColor::GreenColor     = cqColor::fRGBA(0.6f, 0.8f, 0.4f, 1.f);
const cqColor cqColor::BlueColor      = cqColor::fRGBA(0.0f, 0.4f, 0.8f, 1.f);
const cqColor cqColor::CyanColor      = cqColor::fRGBA(0.6f, 0.8f, 0.8f, 1.f);
const cqColor cqColor::YellowColor    = cqColor::fRGBA(1.0f, 1.0f, 0.7f, 1.f);
const cqColor cqColor::MagentaColor   = cqColor::fRGBA(0.8f, 0.0f, 0.6f, 1.f);
const cqColor cqColor::OrangeColor    = cqColor::fRGBA(1.0f, 0.8f, 0.0f, 1.f);
const cqColor cqColor::PurpleColor    = cqColor::fRGBA(0.5f, 0.0f, 0.5f, 1.f);
const cqColor cqColor::BrownColor     = cqColor::fRGBA(0.6f, 0.4f, 0.2f, 1.f);
const cqColor cqColor::ClearColor     = cqColor::fRGBA(0.0f, 0.0f, 0.0f, 0.f);
