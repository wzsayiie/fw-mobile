//

@interface CQSingletonManager : NSObject

+ (instancetype)sharedObject;

- (id)objectForClass:(Class)clazz;

@end
