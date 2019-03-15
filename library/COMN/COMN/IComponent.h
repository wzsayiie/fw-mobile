#import "CORuntime.h"

@interface IComponent : NSObject

- (id)call:(COGUID)m object0:(id)a object1:(id)b object2:(id)c object3:(id)d;
- (id)call:(COGUID)m object0:(id)a object1:(id)b object2:(id)c;
- (id)call:(COGUID)m object0:(id)a object1:(id)b;
- (id)call:(COGUID)m object0:(id)a;

- (int64_t)call:(COGUID)m raw0:(int64_t)a raw1:(int64_t)b raw2:(int64_t)c raw3:(int64_t)d;
- (int64_t)call:(COGUID)m raw0:(int64_t)a raw1:(int64_t)b raw2:(int64_t)c;
- (int64_t)call:(COGUID)m raw0:(int64_t)a raw1:(int64_t)b;
- (int64_t)call:(COGUID)m raw0:(int64_t)a;

@end

@interface IComponentCalleeParams : NSObject
@property (nonatomic) int64_t a0;
@property (nonatomic) int64_t a1;
@property (nonatomic) int64_t a2;
@property (nonatomic) int64_t a3;
@end

@interface IComponentCallee : NSObject {
@public
    id _component;
}
- (void)called:(COGUID)method params:(IComponentCalleeParams *)params ret:(int64_t *)ret;
@end
