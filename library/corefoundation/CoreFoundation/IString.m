#import "IString.h"

static const COGUID mthdSetUTF8    = COGUIDMake(s,e,t,u,t,f,8,_,_,_,_,_,_);
static const COGUID mthdUTF8Data   = COGUIDMake(u,t,f,8,d,a,t,a,_,_,_,_,_);
static const COGUID mthdUTF8Length = COGUIDMake(u,t,f,8,l,e,n,g,t,h,_,_,_);

@implementation IString

- (void)setUTF8WithData:(int64_t)data length:(int32_t)length {
    [self call:mthdSetUTF8 raw0:data raw1:length];
}

- (int64_t)utf8Data {
    return [self call:mthdUTF8Data raw0:0];
}

- (int32_t)utf8Length {
    return (int32_t)[self call:mthdUTF8Length raw0:0];
}

@end

@interface IStringCallee ()
@property (nonatomic, readonly) IString *component;
@end

@implementation IStringCallee

- (IString *)component {
    return _component;
}

- (void)called:(COGUID)method params:(IComponentCalleeParams *)params ret:(int64_t *)ret {
    if (method == mthdSetUTF8) {
        int64_t data = params.a0;
        int32_t length = (int32_t)params.a1;
        [self.component setUTF8WithData:data length:length];
    } else if (method == mthdUTF8Data) {
        *ret = [self.component utf8Data];
    } else if (method == mthdUTF8Length) {
        *ret = [self.component utf8Length];
    }
}

@end

@implementation IString (Native)

- (void)setNSString:(NSString *)string {
    if (string.UTF8String != NULL) {
        const char *data = string.UTF8String;
        int32_t length = (int32_t)strlen(data);
        [self setUTF8WithData:(int64_t)data length:length];
    } else {
        [self setUTF8WithData:0 length:0];
    }
}

- (NSString *)NSString {
    const char *cstring = (const char *)self.utf8Data;
    return cstring != NULL ? @(cstring) : nil;
}

@end
