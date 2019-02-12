#import "CQBridge.h"

NSString *CQGetNSString(CQValue value) {
    const char *str = CQGetStringValue(value);
    int32_t len = CQGetStringLength(value);
    return [[NSString alloc] initWithBytes:str length:len encoding:NSUTF8StringEncoding];
}
