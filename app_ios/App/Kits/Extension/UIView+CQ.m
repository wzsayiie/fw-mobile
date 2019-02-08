#import "UIView+CQ.h"

@implementation UIView (CQ)

- (NSLayoutConstraint *)constraint:(UIView *)subview align:(NSLayoutAttribute)direction {
    return [NSLayoutConstraint constraintWithItem:subview
                                        attribute:direction
                                        relatedBy:NSLayoutRelationEqual
                                           toItem:self
                                        attribute:direction
                                       multiplier:1
                                         constant:0];
}

- (void)addFillingSubview:(UIView *)subview {
    if (subview == nil) {
        return;
    }
    
    [self addSubview:subview];
    self.translatesAutoresizingMaskIntoConstraints = NO;
    NSLayoutConstraint *a = [self constraint:subview align:NSLayoutAttributeTop   ];
    NSLayoutConstraint *b = [self constraint:subview align:NSLayoutAttributeBottom];
    NSLayoutConstraint *c = [self constraint:subview align:NSLayoutAttributeLeft  ];
    NSLayoutConstraint *d = [self constraint:subview align:NSLayoutAttributeRight ];
    [self addConstraints:@[a, b, c, d]];
}

@end
