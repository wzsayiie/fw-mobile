#import <Foundation/Foundation.h>

void _CQLogger_info (const char *file, int line, NSString *format, ...) NS_FORMAT_FUNCTION(3, 4);
void _CQLogger_error(const char *file, int line, NSString *format, ...) NS_FORMAT_FUNCTION(3, 4);

#define I(...) _CQLogger_info (__FILE__, __LINE__, __VA_ARGS__)
#define E(...) _CQLogger_error(__FILE__, __LINE__, __VA_ARGS__)
