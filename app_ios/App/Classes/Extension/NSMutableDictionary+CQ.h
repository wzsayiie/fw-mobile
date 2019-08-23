//

@interface NSMutableDictionary<KeyType, ObjectType> (CQ)

- (void)safeSetObject:(ObjectType)object forKey:(KeyType<NSCopying>)key;

@end
