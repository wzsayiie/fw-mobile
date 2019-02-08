#import "CQSceneNavigator.h"

@interface UIViewController (CQSceneNavigator)

@property (nonatomic, strong) CQSceneDataItem *sceneData;

- (void)finishScene;

@end
