//

//array:
@interface NSMutableArray<ObjectType> (CQ)

- (void)safeAddObject:(ObjectType)object;
- (void)safeInsertObject:(ObjectType)object atIndex:(NSUInteger)index;
- (void)safeRemoveLastObject;
- (void)safeRemoveObjectAtIndex:(NSUInteger)index;
- (void)safeReplaceObjectAtIndex:(NSUInteger)index withObject:(ObjectType)object;

@end

//dictionary:
@interface NSMutableDictionary<KeyType, ObjectType> (CQ)

- (void)safeRemoveObjectForKey:(KeyType)key;
- (void)safeSetObject:(ObjectType)object forKey:(KeyType<NSCopying>)key;

@end

//set:
@interface NSMutableSet<ObjectType> (CQ)

- (void)safeAddObject:(ObjectType)object;
- (void)safeRemoveObject:(ObjectType)object;

@end
