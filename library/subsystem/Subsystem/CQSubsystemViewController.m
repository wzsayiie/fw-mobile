#import "CQSubsystemViewController.h"
#import "CQSubsystemManager.h"
#import "CQFoundation.h"

@interface CQSubsystemViewController ()
@property (nonatomic) NSString *subsystemName;
@end

@implementation CQSubsystemViewController

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    if (self = [super initWithCoder:aDecoder]) {
        self.subsystemName = CQSubsystemManager.sharedObject.startingSubsystemName;
    }
    return self;
}

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if (self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil]) {
        self.subsystemName = CQSubsystemManager.sharedObject.startingSubsystemName;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)removeFromUI {
    [CQSubsystemManager.sharedObject stopSubsystem:self.subsystemName];
}

@end
