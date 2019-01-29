//

@interface KTSingletonManager : NSObject

+ (instancetype)sharedObject;

- (id)objectForClass:(Class)clazz;

@end
