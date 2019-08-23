#import "NSNotificationCenter+CQ.h"

@implementation NSNotificationCenter (CQ)

+ (void)post:(NSString *)name param:(NSObject *)param {
    if (name.length == 0) {
        E(@"try post a empty event name");
        return;
    }
    
    I(@"post event '%@' with param %@", name, param);
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    [center postNotificationName:name object:param];
}

+ (void)addObserver:(NSObject *)observer selector:(SEL)selector name:(NSString *)name {
    if (observer == nil) {
        E(@"try add a nil object as observer");
        return;
    }
    
    NSString *className = NSStringFromClass(observer.class);
    if (selector == NULL) {
        E(@"add observer '%@', but try bind a empty selector", className);
        return;
    }
    if (name.length == 0) {
        E(@"add observer '%@', but don't specify corresponding event", className);
        return;
    }
    
    I(@"add observer '%@:%ld' for '%@'", className, (long)observer.hash, name);
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    [center addObserver:observer selector:selector name:name object:nil];
}

+ (void)removeObserver:(NSObject *)observer {
    if (observer == nil) {
        E(@"try remove a nil observer");
        return;
    }
    
    I(@"remove observer '%@:%ld'", NSStringFromClass(observer.class), (long)observer.hash);
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    [center removeObserver:observer];
}

@end
