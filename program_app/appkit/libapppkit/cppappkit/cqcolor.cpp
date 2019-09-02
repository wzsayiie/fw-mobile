#include "cqcolor.hh"

cqColor::cqColor() /* ........................... */ : red(1), blue(1), green(1), alpha(1) {}
cqColor::cqColor(float r, float b, float g) /* .. */ : red(r), blue(b), green(g), alpha(1) {}
cqColor::cqColor(float r, float b, float g, float a) : red(r), blue(b), green(g), alpha(a) {}

const cqColor cqColor::BlackColor    (0.0, 0.0, 0.0);
const cqColor cqColor::DarkGrayColor (0.3, 0.3, 0.3);
const cqColor cqColor::LightGrayColor(0.6, 0.6, 0.6);
const cqColor cqColor::WhiteColor    (1.0, 1.0, 1.0);
const cqColor cqColor::GrayColor     (0.5, 0.5, 0.5);
const cqColor cqColor::RedColor      (1.0, 0.0, 0.0);
const cqColor cqColor::GreenColor    (0.0, 1.0, 0.0);
const cqColor cqColor::BlueColor     (0.0, 0.0, 1.0);
const cqColor cqColor::CyanColor     (0.0, 1.0, 1.0);
const cqColor cqColor::YellowColor   (1.0, 1.0, 0.0);
const cqColor cqColor::MagentaColor  (1.0, 0.0, 1.0);
const cqColor cqColor::OrangeColor   (1.0, 0.5, 0.0);
const cqColor cqColor::PurpleColor   (0.5, 0.0, 0.5);
const cqColor cqColor::BrownColor    (0.6, 0.4, 0.2);
const cqColor cqColor::ClearColor    (0.0, 0.0, 0.0, 0.0);
