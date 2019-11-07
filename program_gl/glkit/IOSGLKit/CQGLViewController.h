#import <GLKit/GLKit.h>

@interface CQGLViewController : GLKViewController
@property (nonatomic) void (*coreAppEntry)(void);
@end
