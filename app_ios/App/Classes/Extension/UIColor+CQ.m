#import "UIColor+CQ.h"

#define SHARED_COLOR(R, G, B, A)\
/**/    do {\
/**/        static UIColor *color = nil;\
/**/        static dispatch_once_t token = 0;\
/**/        dispatch_once(&token, ^{\
/**/            color = [UIColor colorWithRed:R green:G blue:B alpha:A];\
/**/        });\
/**/        return color;\
/**/    } while (0)

@implementation UIColor (CQ)

+ (UIColor *)softBlackColor     { SHARED_COLOR(0.0f, 0.0f, 0.0f, 1.f); }
+ (UIColor *)softDarkGrayColor  { SHARED_COLOR(0.3f, 0.3f, 0.3f, 1.f); }
+ (UIColor *)softLightGrayColor { SHARED_COLOR(0.6f, 0.6f, 0.6f, 1.f); }
+ (UIColor *)softWhiteColor     { SHARED_COLOR(1.0f, 1.0f, 1.0f, 1.f); }
+ (UIColor *)softGrayColor      { SHARED_COLOR(0.5f, 0.5f, 0.5f, 1.f); }
+ (UIColor *)softRedColor       { SHARED_COLOR(1.0f, 0.4f, 0.4f, 1.f); }
+ (UIColor *)softGreenColor     { SHARED_COLOR(0.6f, 0.8f, 0.4f, 1.f); }
+ (UIColor *)softBlueColor      { SHARED_COLOR(0.0f, 0.4f, 0.8f, 1.f); }
+ (UIColor *)softCyanColor      { SHARED_COLOR(0.6f, 0.8f, 0.8f, 1.f); }
+ (UIColor *)softYellowColor    { SHARED_COLOR(1.0f, 1.0f, 0.7f, 1.f); }
+ (UIColor *)softMagentaColor   { SHARED_COLOR(0.8f, 0.0f, 0.6f, 1.f); }
+ (UIColor *)softOrangeColor    { SHARED_COLOR(1.0f, 0.8f, 0.0f, 1.f); }
+ (UIColor *)softPurpleColor    { SHARED_COLOR(0.5f, 0.0f, 0.5f, 1.f); }
+ (UIColor *)softBrownColor     { SHARED_COLOR(0.6f, 0.4f, 0.2f, 1.f); }
+ (UIColor *)softClearColor     { SHARED_COLOR(0.0f, 0.0f, 0.0f, 0.f); }

@end
