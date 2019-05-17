#import "CQSceneNavigator.h"

#pragma mark - Configuration & Data

NSString *const CQSceneStyleStack = @"CQSceneStyleStack";
NSString *const CQSceneStyleFloat = @"CQSceneStyleFloat";

@implementation CQSceneConfigurationItem
@end

@implementation CQSceneDataItem
@end

#pragma mark - Navigator

@interface CQSceneNavigator () <UINavigationControllerDelegate>
@property (nonatomic, copy  ) NSArray<CQSceneConfigurationItem *> *configuration;
@property (nonatomic, strong) UINavigationController *navigationController;
@property (nonatomic, weak  ) UIViewController *cachedTopController;
@end

@implementation CQSceneNavigator

+ (instancetype)sharedObject {
    static id object = nil;
    if (object == nil) {
        object = [[self alloc] init];
    }
    return object;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    I(@"scene navigator initializing");
    
    //UI
    self.view.backgroundColor = UIColor.whiteColor;
    
    self.navigationController = [[UINavigationController alloc] init];
    self.navigationController.view.backgroundColor = UIColor.whiteColor;
    self.navigationController.delegate = self;
    [self addFillingSubviewWithController:self.navigationController];
    
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
        [self.navigationController pushViewController:controller animated:YES];
        
    } else if (configurationItem.style == CQSceneStyleFloat) {
        
        I(@"show scene '%@'", newAddress);
        [self addFillingSubviewWithController:controller];
    }
}

- (void)finishScene:(UIViewController *)viewController {
    CQSceneConfigurationItem *configurationItem = viewController.sceneData.configuration;
    if (configurationItem.style == CQSceneStyleStack) {
        
        if (viewController == self.navigationController.topViewController) {
            //clean work will execute in the navigation controller's delegate method.
            //there only pop it.
            [self.navigationController popViewControllerAnimated:YES];
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
        [viewController removeFillingSubviewAndController];
        
    } else {
        
        E(@"unknown scene type");
    }
}

- (void)navigationController:(UINavigationController *)navigationController
       didShowViewController:(UIViewController *)viewController
                    animated:(BOOL)animated
{
    //old top controller
    if (self.cachedTopController != nil) {
        
        //if cached top controller isn't included by the stack,
        //consider that it was popped.
        NSArray *stackControllers = self.navigationController.childViewControllers;
        if (![stackControllers containsObject:self.cachedTopController]) {
            CQSceneDataItem *dataItem = self.cachedTopController.sceneData;
            if (dataItem.response != nil) {
                I(@"scene '%@' reponds result %@", dataItem.address, dataItem.result);
                dataItem.response(dataItem.result);
            }
            I(@"pop scene '%@'", dataItem.address);
        }
    }
    
    //new top controller
    self.cachedTopController = viewController;
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
        
        item.address = scene[@"Address"];
        item.controller = scene[@"Controller"];
        
        NSString *style = scene[@"Style"];
        if ([style isEqualToString:@"Stack"]) {
            item.style = CQSceneStyleStack;
        } else if ([style isEqualToString:@"Float"]) {
            item.style = CQSceneStyleFloat;
        }
        
        item.launch = ((NSNumber *)scene[@"Launch"]).boolValue;
        
        [itemList addObject:item];
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
            [query setObject:@(number) forKey:item.name];
        } else {
            [query setObject:item.value forKey:item.name];
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
