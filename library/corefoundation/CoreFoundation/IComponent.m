#import "IComponent.h"

@interface IComponent ()
@end

@implementation IComponent

- (id)call:(COGUID)method object0:(id)a object1:(id)b object2:(id)c object3:(id)d {
    return nil;
}

- (int64_t)call:(COGUID)method raw0:(int64_t)a raw1:(int64_t)b raw2:(int64_t)c raw3:(int64_t)d {
    return 0;
}

#define M(A, B, C) return [self call:m object0:A object1:B object2:C object3:nil];
#define R(A, B, C) return [self call:m    raw0:A    raw1:B    raw2:C    raw3:0  ];

- (id)call:(COGUID)m object0:(id)__0 object1:(id)__1 object2:(id)__2 {M(__0, __1, __2)}
- (id)call:(COGUID)m object0:(id)__0 object1:(id)__1 /* ect2:(id) */ {M(__0, __1, nil)}
- (id)call:(COGUID)m object0:(id)__0 /* ect1:(id)__1 object2:(id) */ {M(__0, nil, nil)}

- (int64_t)call:(COGUID)m raw0:(int64_t)a raw1:(int64_t)b raw2:(int64_t)c {R(a, b, c)}
- (int64_t)call:(COGUID)m raw0:(int64_t)a raw1:(int64_t)b /* 2:(int64_ */ {R(a, b, 0)}
- (int64_t)call:(COGUID)m raw0:(int64_t)a /* 1:(int64_t)b raw2:(int64_ */ {R(a, 0, 0)}

@end

@implementation IComponentCalleeParams
@end

@implementation IComponentCallee

- (void)called:(COGUID)method params:(IComponentCalleeParams *)params ret:(int64_t *)ret {
}

@end
