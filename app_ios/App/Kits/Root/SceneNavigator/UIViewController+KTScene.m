#import "UIViewController+KTScene.h"

@implementation UIViewController (KTSceneNavigator)

KT_SYNTHESIZE_STRONG(setSceneData, sceneData, KTSceneDataItem *)

- (void)finishScene {
    [KTSceneNavigator.sharedObject finishScene:self];
}

@end
