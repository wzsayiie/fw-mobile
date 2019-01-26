#import <objc/runtime.h>

#define _KT_SYNTHESIZE(ref, setter, getter, ...)\
/**/    - (void)setter:(__VA_ARGS__)value {\
/**/        objc_setAssociatedObject(self, @selector(getter), value, OBJC_ASSOCIATION_##ref##_NONATOMIC);\
/**/    }\
/**/    - (__VA_ARGS__)getter {\
/**/        return objc_getAssociatedObject(self, @selector(getter));\
/**/    }

#define KT_SYNTHESIZE_STRONG(setter, getter, ...) _KT_SYNTHESIZE(RETAIN, setter, getter, __VA_ARGS__)
#define KT_SYNTHESIZE_COPY(  setter, getter, ...) _KT_SYNTHESIZE(COPY  , setter, getter, __VA_ARGS__)
