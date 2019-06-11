#import "UIViewController+CQScene.h"

@implementation UIViewController (CQSceneNavigator)

cq_synthesize_strong(sceneData, setSceneData)

- (void)finishScene {
    [CQSceneNavigator.sharedObject finishScene:self];
}

@end
