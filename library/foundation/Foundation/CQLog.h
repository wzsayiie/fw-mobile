#import <Foundation/Foundation.h>

#ifdef __cplusplus
extern "C" {
#endif
void CQLogInfo (NSString *file, int line, NSString *format, ...) NS_FORMAT_FUNCTION(3, 4);
void CQLogError(NSString *file, int line, NSString *format, ...) NS_FORMAT_FUNCTION(3, 4);
#ifdef __cplusplus
}
#endif

#define I(...) CQLogInfo (@(__FILE__), __LINE__, __VA_ARGS__)
#define E(...) CQLogError(@(__FILE__), __LINE__, __VA_ARGS__)
