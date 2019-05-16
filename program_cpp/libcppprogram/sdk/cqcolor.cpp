#include "cqcolor.hh"

cqColor::cqColor(float r, float b, float g)          : red(r), blue(b), green(g), alpha(0) {}
cqColor::cqColor(float r, float b, float g, float a) : red(r), blue(b), green(g), alpha(a) {}

const cqColor cqColor::blackColor    (0.0, 0.0, 0.0);
const cqColor cqColor::darkGrayColor (0.3, 0.3, 0.3);
const cqColor cqColor::lightGrayColor(0.6, 0.6, 0.6);
const cqColor cqColor::whiteColor    (1.0, 1.0, 1.0);
const cqColor cqColor::grayColor     (0.5, 0.5, 0.5);
const cqColor cqColor::redColor      (1.0, 0.0, 0.0);
const cqColor cqColor::greenColor    (0.0, 1.0, 0.0);
const cqColor cqColor::blueColor     (0.0, 0.0, 1.0);
const cqColor cqColor::cyanColor     (0.0, 1.0, 1.0);
const cqColor cqColor::yellowColor   (1.0, 1.0, 0.0);
const cqColor cqColor::magentaColor  (1.0, 0.0, 1.0);
const cqColor cqColor::orangeColor   (1.0, 0.5, 0.0);
const cqColor cqColor::purpleColor   (0.5, 0.0, 0.5);
const cqColor cqColor::brownColor    (0.6, 0.4, 0.2);
const cqColor cqColor::clearColor    (0.0, 0.0, 0.0, 0.0);
