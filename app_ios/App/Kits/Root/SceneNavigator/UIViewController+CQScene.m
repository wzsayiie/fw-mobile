#import "UIViewController+CQScene.h"

@implementation UIViewController (CQSceneNavigator)

cq_synthesize_strong((CQSceneDataItem *), sceneData, setSceneData)

- (void)finishScene {
    [CQSceneNavigator.sharedObject finishScene:self];
}

@end
