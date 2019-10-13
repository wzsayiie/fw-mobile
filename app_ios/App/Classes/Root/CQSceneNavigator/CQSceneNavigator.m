#import "CQSceneNavigator.h"

#pragma mark - Configuration & Data

NSString *const CQSceneStyleStack = @"CQSceneStyleStack";
NSString *const CQSceneStyleFloat = @"CQSceneStyleFloat";

@implementation CQSceneConfigurationItem
@end

@implementation CQSceneDataItem
@end

#pragma mark - Navigator

@interface CQSceneNavigator () <UINavigationControllerDelegate, UIGestureRecognizerDelegate>
@property (nonatomic, copy  ) NSArray<CQSceneConfigurationItem *> *configuration;
@property (nonatomic, strong) UINavigationController *stackNavigationController;
@property (nonatomic, weak  ) UIViewController *stackTopController;
@end

@implementation CQSceneNavigator

+ (instancetype)sharedObject {
    CQ_SHARED_OBJECT(self);
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    I(@"scene navigator initializing");
    
    //UI
    self.view.backgroundColor = UIColor.whiteColor;
    
    self.stackNavigationController = [[UINavigationController alloc] init];
    self.stackNavigationController.view.backgroundColor = UIColor.whiteColor;
    self.stackNavigationController.delegate = self;
    self.stackNavigationController.interactivePopGestureRecognizer.delegate = self;
    [self safeAddChildController:self.stackNavigationController];
    
    //load configuration
    self.configuration = [self loadConfiguration];
    
    //launch scenes
    CQSceneConfigurationItem *stackItem = nil;
    CQSceneConfigurationItem *floatItem = nil;
    for (CQSceneConfigurationItem *item in self.configuration) {
        if (stackItem == nil && item.style == CQSceneStyleStack && item.launch) {
            stackItem = item;
        }
        if (floatItem == nil && item.style == CQSceneStyleFloat && item.launch) {
            floatItem = item;
        }
        if (stackItem != nil && floatItem != nil) {
            break;
        }
    }
    
    if (stackItem != nil) {
        I(@"request launch stack scene '%@'", stackItem.address);
        [self request:stackItem.address query:nil response:nil];
    } else {
        I(@"not found launch stack scene");
    }
    
    if (floatItem != nil) {
        I(@"request launch float scene '%@'", floatItem.address);
        [self request:floatItem.address query:nil response:nil];
    } else {
        I(@"not found launch float scene");
    }
}

- (void)request:(NSString *)address
          query:(NSDictionary<NSString *, id> *)query
       response:(void (^)(NSDictionary<NSString *, id> *))response
{
    //1 check environment context
    if (address.length == 0) {
        E(@"specifying navigation scene address is empty");
        return;
    }
    
    CQSceneConfigurationItem *configurationItem = nil;
    for (CQSceneConfigurationItem *item in self.configuration) {
        if ([address hasPrefix:item.address]) {
            configurationItem = item;
            break;
        }
    }
    if (configurationItem == nil) {
        E(@"unknown navigation scene '%@'", address);
        return;
    }
    
    //2 instaniate view controller
    if (configurationItem.controller.length == 0) {
        E(@"not specify controller can handle scene '%@'", address);
        return;
    }
    UIViewController *controller = [[NSClassFromString(configurationItem.controller) alloc] init];
    if (controller == nil) {
        E(@"instaniate controller failed for scene '%@'", address);
        return;
    }
    
    NSMutableDictionary *newQuery = [NSMutableDictionary dictionaryWithDictionary:query];
    NSString *newAddress = [self mergeQueryFromAddress:address query:newQuery];
    
    controller.sceneData = [[CQSceneDataItem alloc] init];
    controller.sceneData.configuration = configurationItem;
    controller.sceneData.address = newAddress;
    controller.sceneData.query = newQuery;
    controller.sceneData.result = [NSMutableDictionary dictionary];
    controller.sceneData.response = response;
    
    //3 show
    if (configurationItem.style == CQSceneStyleStack) {
        
        I(@"push scene '%@'", newAddress);
        controller.edgesForExtendedLayout = UIRectEdgeNone;
        [self.stackNavigationController pushViewController:controller animated:YES];
        
    } else if (configurationItem.style == CQSceneStyleFloat) {
        
        I(@"show scene '%@'", newAddress);
        [self safeAddChildController:controller];
    }
}

- (void)finishScene:(UIViewController *)viewController {
    CQSceneConfigurationItem *configurationItem = viewController.sceneData.configuration;
    if (configurationItem.style == CQSceneStyleStack) {
        
        if (viewController == self.stackNavigationController.topViewController) {
            //clean work will execute in the navigation controller's delegate method.
            //there only pop it.
            [self.stackNavigationController popViewControllerAnimated:YES];
        } else {
            E(@"try pop a controller but it is't top controller");
        }
        
    } else if (configurationItem.style == CQSceneStyleFloat) {
        CQSceneDataItem *dataItem = viewController.sceneData;
        
        if (![self.childViewControllers containsObject:viewController]) {
            E(@"can not remove '%@' cause it's not child of the navigation", dataItem.address);
            return;
        }
        
        if (dataItem.response != nil) {
            I(@"scene '%@' reponds result %@", dataItem.address, dataItem.result);
            dataItem.response(dataItem.result);
        }
        I(@"remove scene '%@'", dataItem.address);
        [viewController safeRemoveFromParentController];
        
    } else {
        
        E(@"unknown scene type");
    }
}

- (void)navigationController:(UINavigationController *)stackNavigationController
      willShowViewController:(UIViewController *)newStackTopController
                    animated:(BOOL)animated
{
    if (self.stackTopController == newStackTopController) {
        return;
    }
    
    //NOTE: set $animal to YES.
    //
    //for interactive pop gesture, if user does not pop the topest controller finally,
    //when the topest controller returns to nomral,
    //app will be not receive "didShowViewController" callback.
    //
    //set $animal to YES, the status of the navigation bar is not reset immediately.
    [self adjustNavigationBarForController:newStackTopController animated:YES];
}

- (void)navigationController:(UINavigationController *)stackNavigationController
       didShowViewController:(UIViewController *)newStackTopController
                    animated:(BOOL)animated
{
    if (self.stackTopController == newStackTopController) {
        return;
    }
    
    //old top controller:
    if (self.stackTopController != nil) {
        
        //if stack top controller isn't included by the stack, consider that it was popped.
        NSArray *stackControllers = self.stackNavigationController.childViewControllers;
        if (![stackControllers containsObject:self.stackTopController]) {
            CQSceneDataItem *dataItem = self.stackTopController.sceneData;
            if (dataItem.response != nil) {
                I(@"scene '%@' reponds result %@", dataItem.address, dataItem.result);
                dataItem.response(dataItem.result);
            }
            I(@"pop scene '%@'", dataItem.address);
        }
    }
    
    //new top controller:
    self.stackTopController = newStackTopController;
    [self adjustNavigationBarForController:newStackTopController animated:NO];
}

- (void)adjustNavigationBarForController:(UIViewController *)controller animated:(BOOL)animated {
    
    BOOL wantNavigable = controller.sceneData.configuration.navigable;
    BOOL currentNavigable = !self.stackNavigationController.navigationBar.hidden;
    
    if (wantNavigable && !currentNavigable) {
        [self.stackNavigationController setNavigationBarHidden:NO animated:animated];
    } else if (!wantNavigable && currentNavigable) {
        [self.stackNavigationController setNavigationBarHidden:YES animated:animated];
    }
}

//interactive pop gesture is always available.
- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer {
    return self.stackNavigationController.childViewControllers.count >= 1;
}

- (NSArray<CQSceneConfigurationItem *> *)loadConfiguration {
    
    NSString *fileName = @"Scenes.plist";
    
    NSString *filePath = [NSBundle.mainBundle pathForResource:fileName ofType:nil];
    if (filePath.length == 0) {
        E(@"not found scene description file '%@'", fileName);
        return nil;
    }
    I(@"got scene description file '%@'", fileName);
    
    NSArray<NSDictionary *> *sceneList = [NSArray arrayWithContentsOfFile:filePath];
    if (sceneList.count == 0) {
        E(@"not found scene info from '%@'", fileName);
        return nil;
    }
    
    NSMutableArray<CQSceneConfigurationItem *> *itemList = [NSMutableArray array];
    for (NSDictionary *scene in sceneList) {
        CQSceneConfigurationItem *item = [[CQSceneConfigurationItem alloc] init];
        
        NSString *string = nil;
        NSNumber *number = nil;
        
        //address:
        if ((string = scene[@"address"]) != nil) {
            item.address = string;
        }
        //controller:
        if ((string = scene[@"controller"]) != nil) {
            item.controller = string;
        }
        //style:
        if ((string = scene[@"style"]) != nil) {
            if /**/ ([string isEqualToString:@"stack"]) {item.style = CQSceneStyleStack;}
            else if ([string isEqualToString:@"float"]) {item.style = CQSceneStyleFloat;}
            else /* ................................ */ {item.style = nil              ;}
        }
        //navigable:
        if ((number = scene[@"navigable"]) != nil) {
            item.navigable = number.boolValue;
        } else {
            item.navigable = YES; //default.
        }
        //number:
        if ((number = scene[@"launch"]) != nil) {
            item.launch = number.boolValue;
        }
        
        [itemList safeAddObject:item];
    }
    return itemList;
}

- (NSString *)mergeQueryFromAddress:(NSString *)address query:(NSMutableDictionary<NSString *, id> *)query {
    
    //1 get new address without query
    NSMutableString *newAddress = [NSMutableString string]; {
        NSUInteger split = [address rangeOfString:@"?"].location;
        if (split != NSNotFound) {
            NSString *head = [address substringWithRange:NSMakeRange(0, split)];
            [newAddress appendString:head];
        } else {
            [newAddress appendString:address];
        }
    }
    
    //2 get query from address and merge it to the dictionary
    NSURLComponents *components = [NSURLComponents componentsWithString:address];
    for (NSURLQueryItem *item in components.queryItems) {
        if ([query.allKeys containsObject:item.name]) {
            E(@"same key '%@' from the address and the query", item.name);
            continue;
        }
        
        NSScanner *scanner = [NSScanner scannerWithString:item.value];
        int number = 0;
        if ([scanner scanInt:&number] && scanner.isAtEnd) {
            [query safeSetObject:@(number) forKey:item.name];
        } else {
            [query safeSetObject:item.value forKey:item.name];
        }
    }
    
    //3 add merged query to new address
    char link = '?';
    for (NSString *key in query) {
        [newAddress appendFormat:@"%c%@=%@", link, key, query[key]];
        link = '&';
    }
    
    return newAddress;
}

@end
