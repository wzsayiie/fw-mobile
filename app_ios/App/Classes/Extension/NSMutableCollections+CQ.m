#import "NSMutableCollections+CQ.h"

//array:

@implementation NSMutableArray (CQ)

- (void)safeAddObject:(id)object {
    if (object != nil) {
        [self addObject:object];
    }
}

- (void)safeInsertObject:(id)object atIndex:(NSUInteger)index {
    //NOTE: index can equal to the array length.
    if(object != nil && index <= self.count) {
        [self insertObject:object atIndex:index];
    }
}

- (void)safeRemoveLastObject {
    [self removeLastObject];
}

- (void)safeRemoveObjectAtIndex:(NSUInteger)index {
    if (index < self.count) {
        [self removeObjectAtIndex:index];
    }
}

- (void)safeReplaceObjectAtIndex:(NSUInteger)index withObject:(id)object {
    if (index < self.count && object != nil) {
        [self replaceObjectAtIndex:index withObject:object];
    }
}

@end

//dictionary:

@implementation NSMutableDictionary (CQ)

- (void)safeRemoveObjectForKey:(id)key {
    if (key != nil) {
        [self removeObjectForKey:key];
    }
}

- (void)safeSetObject:(id)object forKey:(id<NSCopying>)key {
    if (object != nil && key != nil) {
        [self setObject:object forKey:key];
    }
}

@end

//set:

@implementation NSMutableSet (CQ)

- (void)safeAddObject:(id)object {
    if (object != nil) {
        [self addObject:object];
    }
}

- (void)safeRemoveObject:(id)object {
    if (object != nil) {
        [self removeObject:object];
    }
}

@end
