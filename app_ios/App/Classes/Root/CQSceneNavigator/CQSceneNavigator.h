//

#pragma mark - Configuration Item

extern NSString *const CQSceneStyleStack;
extern NSString *const CQSceneStyleFloat;

@interface CQSceneConfigurationItem : NSObject
@property (nonatomic, copy) NSString *address;
@property (nonatomic, copy) NSString *controller;
@property (nonatomic, copy) NSString *style;
@property (nonatomic) BOOL navigable; //default YES.
@property (nonatomic) BOOL launch;    //default NO.
@end

#pragma mark - Data Item

@interface CQSceneDataItem : NSObject
@property (nonatomic, strong) CQSceneConfigurationItem *configuration;
@property (nonatomic, copy  ) NSString *address;
@property (nonatomic, copy  ) NSDictionary<NSString *, id> *query;
@property (nonatomic, strong) NSMutableDictionary<NSString *, id> *result;
@property (nonatomic, strong) void (^response)(NSDictionary<NSString *, id> *);
@end

#pragma mark - Navigator

@interface CQSceneNavigator : UIViewController

+ (instancetype)sharedObject;

- (void)request:(NSString *)address
          query:(NSDictionary<NSString *, id> *)query
       response:(void (^)(NSDictionary<NSString *, id> *))response;

- (void)finishScene:(UIViewController *)viewController;

@end
