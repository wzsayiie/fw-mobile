#import "KTSingletonManager.h"

@interface KTSingletonManager ()
@property (nonatomic, strong) NSMutableDictionary<Class, NSObject *> *objects;
@end

@implementation KTSingletonManager

+ (instancetype)sharedObject {
    static KTSingletonManager *manager = nil;
    if (manager == nil) {
        manager = [[self alloc] init];
        manager.objects = [[NSMutableDictionary alloc] init];
        [manager loadQuickModels];
    }
    return manager;
}

- (void)loadQuickModels {
    
    NSString *fileName = @"QuickModels.plist";
    
    NSString *filePath = [NSBundle.mainBundle pathForResource:fileName ofType:nil];
    if (filePath.length == 0) {
        E(@"not found model description file '%@'", fileName);
        return;
    }
    I(@"got model description file '%@'", fileName);
    
    NSArray<NSString *> *nameList = [NSArray arrayWithContentsOfFile:filePath];
    if (nameList.count == 0) {
        E(@"could not get model names from '%@'", fileName);
        return;
    }
    
    I(@"initialize quick models");
    for (NSString *name in nameList) {
        
        if (name.length == 0) {
            E(@"there was a empty item in '%@'", fileName);
            continue;
        }
        
        Class clazz = NSClassFromString(name);
        if (clazz == nil) {
            E(@"there was no class named '%@'", name);
            continue;
        }
        
        [self objectForClass:clazz];
    }
}

- (id)objectForClass:(Class)clazz {
    if (clazz == Nil) {
        E(@"the parameters was should not a null");
        return nil;
    }
    
    NSObject *object = self.objects[clazz];
    if (object == nil) {
        I(@"initialize model '%@'", NSStringFromClass(clazz));
        object = [[clazz alloc] init];
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-W" "incompatible-pointer-types"
        self.objects[clazz] = object;
#pragma clang diagnostic pop
    }
    return object;
}

@end
