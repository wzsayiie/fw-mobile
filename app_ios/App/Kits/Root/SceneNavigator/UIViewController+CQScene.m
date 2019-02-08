#import "UIViewController+CQScene.h"

@implementation UIViewController (CQSceneNavigator)

CQ_SYNTHESIZE_STRONG(setSceneData, sceneData, CQSceneDataItem *)

- (void)finishScene {
    [CQSceneNavigator.sharedObject finishScene:self];
}

@end
