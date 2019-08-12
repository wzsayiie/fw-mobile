//

@interface NSNotificationCenter (CQ)

+ (void)post:(NSString *)name param:(NSObject *)param;
+ (void)addObserver:(NSObject *)observer selector:(SEL)selector name:(NSString *)name;

+ (void)removeObserver:(NSObject *)observer;

@end
