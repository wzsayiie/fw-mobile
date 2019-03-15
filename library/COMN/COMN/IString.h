#import "IComponent.h"

static const COGUID IStringGUID = COGUIDMake(i,s,t,r,i,n,g,_,_,_,_,_,_);

@interface IString : IComponent
- (void)setUTF8WithData:(int64_t)data length:(int32_t)length;
- (int64_t)utf8Data;
- (int32_t)utf8Length;
@end

@interface IStringCallee : IComponentCallee
@end

@interface IString (Native)
@property (nonatomic) NSString *NSString;
@end
