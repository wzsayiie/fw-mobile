#import "CQSubsystemManager.h"
#import "CQDefaultSubsystemController.h"
#import "CQFoundation.h"
#import <UIKit/UIKit.h>

@interface CQSubsystemInfo : NSObject
@property (nonatomic) BOOL startedByDelegate;
@property (nonatomic) UIViewController *controller;
@end
@implementation CQSubsystemInfo
@end

@interface CQSubsystemManager ()
@property (nonatomic) NSDictionary<NSString *, Class> *controllerClassNames;
@property (nonatomic) NSMutableDictionary<NSString *, CQSubsystemInfo *> *runningSubsystemInfos;
@property (nonatomic) NSMutableArray<NSString *> *lastStartedSubsystemNames;
@end

@implementation CQSubsystemManager

+ (instancetype)sharedObject {
    static id object = nil;
    if (object == nil) {
        object = [[self alloc] init];
    }
    return object;
}

- (NSDictionary<NSString *, Class> *)controllerClassNames {
    if (_controllerClassNames == nil) {
        _controllerClassNames = @{
            @"default":CQDefaultSubsystemController.class
        };
    }
    return _controllerClassNames;
}

- (NSMutableDictionary<NSString *, CQSubsystemInfo *> *)runningSubsystemInfos {
    if (_runningSubsystemInfos == nil) {
        _runningSubsystemInfos = [NSMutableDictionary dictionary];
    }
    return _runningSubsystemInfos;
}

- (NSMutableArray<NSString *> *)lastStartedSubsystemNames {
    if (_lastStartedSubsystemNames == nil) {
        _lastStartedSubsystemNames = [NSMutableArray array];
    }
    return _lastStartedSubsystemNames;
}

- (NSString *)popLastStartedSubsystemName {
    if (self.lastStartedSubsystemNames.count > 0) {
        NSString *first = self.lastStartedSubsystemNames[0];
        [self.lastStartedSubsystemNames removeObjectAtIndex:0];
        return first;
    } else {
        return nil;
    }
}

- (BOOL)startSubsystem:(NSString *)name {
    if (name.length == 0) {
        E(@"try start subsystem but specified name is empty");
        return NO;
    }
    if (self.runningSubsystemInfos[name] != nil) {
        E(@"try start subsystem '%@' but it's already running", name);
        return NO;
    }

    //record this name, for the subsystem controller could find own one.
    [self.lastStartedSubsystemNames addObject:name];
    
    CQSubsystemInfo *subsystemInfo = nil;
    if (self.delegate == nil) do {
        I(@"try start subsystem '%@' with default method", name);
        
        Class clazz = self.controllerClassNames[name];
        if (clazz == Nil) {
            E(@"not find corresponding controller for subsystem '%@'", name);
            break;
        }
        UIViewController *controller = [[clazz alloc] init];
        UIWindow *window = UIApplication.sharedApplication.delegate.window;
        UIViewController *root = window.rootViewController;
        [root presentViewController:controller animated:YES completion:nil];
        
        subsystemInfo = [[CQSubsystemInfo alloc] init];
        subsystemInfo.startedByDelegate = NO;
        subsystemInfo.controller = controller;
        
    } while (0); else {
        I(@"try start subsystem '%@' with delegate", name);
        
        BOOL succeeded = [self.delegate subsystemManager:self startSubsystem:name];
        if (succeeded) {
            subsystemInfo = [[CQSubsystemInfo alloc] init];
            subsystemInfo.startedByDelegate = YES;
            subsystemInfo.controller = nil;
        }
    }
    
    if (subsystemInfo != nil) {
        I(@"start subsystem succeeded");
        self.runningSubsystemInfos[name] = subsystemInfo;
        return YES;
    } else {
        E(@"start subsystem failed");
        return NO;
    }
}

- (void)stopSubsystem:(NSString *)name {
    if (name.length == 0) {
        E(@"try stop subsystem but specified name is empty");
        return;
    }
    
    CQSubsystemInfo *subsystemInfo = self.runningSubsystemInfos[name];
    if (subsystemInfo == nil) {
        E(@"try stop subsystem '%@' but it's not running", name);
        return;
    }
    [self.runningSubsystemInfos removeObjectForKey:name];
    
    if (subsystemInfo.startedByDelegate) {
        if (self.delegate != nil) {
            I(@"stop subsystem '%@' with delegate", name);
            [self.delegate subsystemManager:self stopSubsystem:name];
        } else {
            E(@"the delegate was released, can't stop subsystem '%@'", name);
        }
    } else {
        I(@"stop subsystem '%@' with default method", name);
        [subsystemInfo.controller dismissViewControllerAnimated:YES completion:nil];
    }
}

@end
