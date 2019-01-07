//

#pragma mark - Configuration Item

extern NSString *const KTSceneStyleStack;
extern NSString *const KTSceneStyleFloat;

@interface KTSceneConfigurationItem : NSObject
@property (nonatomic, copy  ) NSString *address;
@property (nonatomic, copy  ) NSString *controller;
@property (nonatomic, copy  ) NSString *style;
@property (nonatomic, assign) BOOL      launch;
@end

#pragma mark - Data Item

@interface KTSceneDataItem : NSObject
@property (nonatomic, strong) KTSceneConfigurationItem *configuration;
@property (nonatomic, copy  ) NSString *address;
@property (nonatomic, copy  ) NSDictionary<NSString *, id> *query;
@property (nonatomic, strong) NSMutableDictionary<NSString *, id> *result;
@property (nonatomic, strong) void (^response)(NSDictionary<NSString *, id> *);
@end

#pragma mark - Navigator

@interface KTSceneNavigator : UIViewController

+ (instancetype)sharedObject;

- (void)request:(NSString *)address
          query:(NSDictionary<NSString *, id> *)query
       response:(void (^)(NSDictionary<NSString *, id> *))response;

- (void)finishScene:(UIViewController *)viewController;

@end
