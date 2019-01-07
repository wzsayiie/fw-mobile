#import "BRGBridge.h"

// stack parameters ->

void BRGWriteString(NSString *string) {
    BRGWriteStringLength((int)string.length);
    BRGWriteStringValue(string.UTF8String, (int)string.length);
}

static void BRGWriteObject(id object) {
    if /**/ ([object isKindOfClass:NSNumber.class    ]) { BRGWriteLong([object longValue]); }
    else if ([object isKindOfClass:NSString.class    ]) { BRGWriteString(object); }
    else if ([object isKindOfClass:NSArray.class     ]) { BRGWriteArray(object); }
    else if ([object isKindOfClass:NSDictionary.class]) { BRGWriteDictionary(object); }
}

void BRGWriteArray(NSArray *array) {
    BRGWriteArraySize((int)array.count);
    for (id item in array) {
        BRGWriteObject(item);
    }
}

void BRGWriteDictionary(NSDictionary *dictionary) {
    BRGWriteMapSize((int)dictionary.count);
    for (id key in dictionary) {
        BRGWriteObject(key);
        BRGWriteObject(dictionary[key]);
    }
}

NSString *BRGReadString(void) {
    BRGReadStringLength();
    return [[NSString alloc] initWithUTF8String:BRGReadStringValue()];
}

static id BRGReadObject(void) {
    switch (BRGCheckType()) {
        
        case BRGTypeBool  : return @(BRGReadBool  ());
        case BRGTypeByte  : return @(BRGReadByte  ());
        case BRGTypeShort : return @(BRGReadShort ());
        case BRGTypeInt   : return @(BRGReadInt   ());
        case BRGTypeLong  : return @(BRGReadLong  ());
        case BRGTypeFloat : return @(BRGReadFloat ());
        case BRGTypeDouble: return @(BRGReadDouble());

        case BRGTypeStringLength: return BRGReadString();
        case BRGTypeArraySize: return BRGReadArray();
        case BRGTypeMapSize: return BRGReadArray();
            
        default: return nil;
    }
}

NSArray *BRGReadArray(void) {
    int size = BRGReadArraySize();
    NSMutableArray *array = [NSMutableArray arrayWithCapacity:size];
    for (int it = 0; it < size; ++it) {
        [array addObject:BRGReadObject()];
    }
    return array;
}

NSDictionary *BRGReadDictionary(void) {
    int size = BRGReadMapSize();
    NSMutableDictionary *dicionary = [NSMutableDictionary dictionaryWithCapacity:size];
    for (int it = 0; it < size; ++it) {
        id key = BRGReadObject();
        id obj = BRGReadObject();
        dicionary[key] = obj;
    }
    return dicionary;
}
