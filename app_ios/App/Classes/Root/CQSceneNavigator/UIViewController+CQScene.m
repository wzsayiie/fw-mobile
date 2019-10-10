#import "UIViewController+CQScene.h"

@implementation UIViewController (CQSceneNavigator)

CQ_SYNTHESIZE_STRONG(sceneData, setSceneData)

- (void)finishScene {
    [CQSceneNavigator.sharedObject finishScene:self];
}

@end
