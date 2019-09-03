#include "cqcolor.hh"

cqColor::cqColor() /* ........................... */ : red(1), green(1), blue(1), alpha(1) {}
cqColor::cqColor(float r, float g, float b) /* .. */ : red(r), green(g), blue(b), alpha(1) {}
cqColor::cqColor(float r, float g, float b, float a) : red(r), green(g), blue(b), alpha(a) {}

const cqColor cqColor::BlackColor    (0.0, 0.0, 0.0);
const cqColor cqColor::DarkGrayColor (0.3, 0.3, 0.3);
const cqColor cqColor::LightGrayColor(0.6, 0.6, 0.6);
const cqColor cqColor::WhiteColor    (1.0, 1.0, 1.0);
const cqColor cqColor::GrayColor     (0.5, 0.5, 0.5);
const cqColor cqColor::RedColor      (1.0, 0.4, 0.4);
const cqColor cqColor::GreenColor    (0.6, 0.8, 0.4);
const cqColor cqColor::BlueColor     (0.0, 0.4, 0.8);
const cqColor cqColor::CyanColor     (0.6, 0.8, 0.8);
const cqColor cqColor::YellowColor   (1.0, 1.0, 0.7);
const cqColor cqColor::MagentaColor  (0.8, 0.0, 0.6);
const cqColor cqColor::OrangeColor   (1.0, 0.8, 0.0);
const cqColor cqColor::PurpleColor   (0.5, 0.0, 0.5);
const cqColor cqColor::BrownColor    (0.6, 0.4, 0.2);
const cqColor cqColor::ClearColor    (0.0, 0.0, 0.0, 0.0);
