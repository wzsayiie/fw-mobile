#import "UIView+CQ.h"
#import <objc/runtime.h>

//layout constraits:

void cq_strain_remove(UIView *holderView, UIView *targetView) {
    if (holderView == nil || targetView == nil) {
        return;
    }
    
    NSMutableArray<NSLayoutConstraint *> *constaints = [NSMutableArray array];
    for (NSLayoutConstraint *it in holderView.constraints) {
        if ([it.firstItem isEqual:targetView] || [it.secondItem isEqual:targetView]) {
            [constaints safeAddObject:it];
        }
    }
    if (constaints.count > 0) {
        [holderView removeConstraints:constaints];
    }
}

static NSMutableArray<NSLayoutConstraint *> *_active_constraits = nil;

void cq_strain_begin(void) {
    _active_constraits = [NSMutableArray array];
}

void cq_strain_set(
    id firstItem , NSLayoutAttribute firstAttr , NSLayoutRelation relation,
    id secondItem, NSLayoutAttribute secondAttr,
    CGFloat multiplier,
    CGFloat constant)
{
    if (_active_constraits == nil) {
        return;
    }
    
    NSLayoutConstraint *constraint =
    [NSLayoutConstraint constraintWithItem:firstItem
                                 attribute:firstAttr
                                 relatedBy:relation
                                    toItem:secondItem
                                 attribute:secondAttr
                                multiplier:multiplier
                                  constant:constant];
    
    [_active_constraits safeAddObject:constraint];
}

void cq_strain_end(UIView *view) {
    if (view != nil && _active_constraits.count > 0) {
        [view addConstraints:_active_constraits];
    }
    _active_constraits = nil;
}

//UIView(CQ):

static void exchangeUIViewMethodsIfNeeded(void);

@interface UIView (CQ_DAT)
@property (nonatomic) NSNumber *currentVoid;
@end

@implementation UIView (CQ_DAT)
CQ_SYNTHESIZE_STRONG(currentVoid, setCurrentVoid)
@end

@implementation UIView (CQ)

- (void)addFillingSubview:(UIView *)subview {
    if (subview == nil) {
        return;
    }
    
    subview.translatesAutoresizingMaskIntoConstraints = NO;
    [self addSubview:subview];
    
    cq_strain_begin();
    cq_strain_set(subview, S_LEFT , S_EQUAL, self, S_LEFT , 1, 0);
    cq_strain_set(subview, S_RIGHT, S_EQUAL, self, S_RIGHT, 1, 0);
    cq_strain_set(subview, S_TOP  , S_EQUAL, self, S_TOP  , 1, 0);
    cq_strain_set(subview, S_BOTT , S_EQUAL, self, S_BOTT , 1, 0);
    cq_strain_end(self);
}

- (void)setIsVoid:(BOOL)isVoid {
    exchangeUIViewMethodsIfNeeded();
    if (isVoid) {
        self.backgroundColor = UIColor.clearColor;
        self.currentVoid = @YES;
    } else {
        self.currentVoid = @NO;
    }
}

- (BOOL)isVoid {
    return self.currentVoid.boolValue;
}

- (UIView *)r_hitTest:(CGPoint)point withEvent:(UIEvent *)event {
    UIView *target = [self r_hitTest:point withEvent:event];
    if (self.currentVoid.boolValue && target == self) {
        return nil;
    }
    return target;
}

@end

static void exchangeUIViewMethodsIfNeeded(void) {
    static dispatch_once_t token = 0;
    dispatch_once(&token, ^{
        Method m1 = class_getInstanceMethod(UIView.class, @selector(r_hitTest:withEvent:));
        Method m2 = class_getInstanceMethod(UIView.class, @selector(hitTest:withEvent:));
        method_exchangeImplementations(m1, m2);
    });
}
