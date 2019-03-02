#import "CQBridge.h"

NSString *CQBridgeGetNSString(CQBridgeValue value) {
    const char *str = CQBridgeStringValue(value);
    int32_t len = CQBridgeStringLength(value);
    return [[NSString alloc] initWithBytes:str length:len encoding:NSUTF8StringEncoding];
}
