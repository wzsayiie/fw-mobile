#import <Foundation/Foundation.h>

#ifdef __cplusplus
extern "C" {
#endif

void _I(const char *file, int line, NSString *format, ...) NS_FORMAT_FUNCTION(3, 4);
void _E(const char *file, int line, NSString *format, ...) NS_FORMAT_FUNCTION(3, 4);

#ifdef __cplusplus
}
#endif

#define I(...) _I(__FILE__, __LINE__, __VA_ARGS__)
#define E(...) _E(__FILE__, __LINE__, __VA_ARGS__)
