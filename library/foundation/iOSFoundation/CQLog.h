#import <Foundation/Foundation.h>
#import "cqcbasis.h"

CQ_C_LINK void CQLogInfo (NSString *file, int line, NSString *format, ...) NS_FORMAT_FUNCTION(3, 4);
CQ_C_LINK void CQLogError(NSString *file, int line, NSString *format, ...) NS_FORMAT_FUNCTION(3, 4);

#define I(...) CQLogInfo (@(__FILE__), __LINE__, __VA_ARGS__)
#define E(...) CQLogError(@(__FILE__), __LINE__, __VA_ARGS__)
