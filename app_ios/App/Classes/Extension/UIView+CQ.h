//

//layout constraits:

//remove constraints that on $holderView about $targetView.
void cq_strain_remove(UIView *holderView, UIView *targetView);

static NSLayoutRelation  S_EQUAL = NSLayoutRelationEqual;
static NSLayoutAttribute S_LEFT  = NSLayoutAttributeLeft;
static NSLayoutAttribute S_RIGHT = NSLayoutAttributeRight;
static NSLayoutAttribute S_TOP   = NSLayoutAttributeTop;
static NSLayoutAttribute S_BOTT  = NSLayoutAttributeBottom;

//add constraints to $view.
void cq_strain_begin(void);

void cq_strain_set(
    id firstItem , NSLayoutAttribute firstAttr , NSLayoutRelation relation,
    id secondItem, NSLayoutAttribute secondAttr,
    CGFloat multiplier,
    CGFloat constant
);

void cq_strain_end(UIView *view);

//UIView(CQ):

@interface UIView (CQ)

- (void)addFillingSubview:(UIView *)subview;

@end
