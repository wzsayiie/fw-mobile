#import <Foundation/Foundation.h>
#import "brg_bridge_core.h"

// stack parameters ->

void BRGWriteString(NSString *string);
void BRGWriteArray(NSArray *array);
void BRGWriteDictionary(NSDictionary *dictionary);

NSString *BRGReadString(void);
NSArray *BRGReadArray(void);
NSDictionary *BRGReadDictionary(void);
