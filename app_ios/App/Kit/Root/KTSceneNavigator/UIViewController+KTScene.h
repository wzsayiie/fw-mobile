#import "KTSceneNavigator.h"

@interface UIViewController (KTSceneNavigator)

@property (nonatomic, strong) KTSceneDataItem *sceneData;

- (void)finishScene;

@end
