#import "CQObjcBasis.h"

void CQSetStrongProperty(id object, const void *key, id value) {
    objc_setAssociatedObject(object, key, value, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

void CQSetCopyProperty(id object, const void *key, id value) {
    objc_setAssociatedObject(object, key, value, OBJC_ASSOCIATION_COPY_NONATOMIC);
}

id CQGetProperty(id object, const void *key) {
    return objc_getAssociatedObject(object, key);
}

//interfaces for interaction with c:

#define S NSString *

struct cq_bytes   *cq_objc_mut_bytes  (NSMutableData              *a) {return (__bridge struct cq_bytes   *)a;}
struct cq_int64s  *cq_objc_mut_int64s (NSMutableArray<NSNumber *> *a) {return (__bridge struct cq_int64s  *)a;}
struct cq_strings *cq_objc_mut_strings(NSMutableArray<NSString *> *a) {return (__bridge struct cq_strings *)a;}
struct cq_ss_map  *cq_objc_mut_ss_map (NSMutableDictionary<S, S>  *a) {return (__bridge struct cq_ss_map  *)a;}

struct cq_bytes   *cq_objc_bytes  (NSData              *a) {return (__bridge struct cq_bytes   *)a;}
struct cq_int64s  *cq_objc_int64s (NSArray<NSNumber *> *a) {return (__bridge struct cq_int64s  *)a;}
struct cq_strings *cq_objc_strings(NSArray<NSString *> *a) {return (__bridge struct cq_strings *)a;}
struct cq_ss_map  *cq_objc_ss_map (NSDictionary<S, S>  *a) {return (__bridge struct cq_ss_map  *)a;}

#undef S

void cq_objc_bytes_recv(struct cq_bytes *dst, const void *ptr, int32_t len) {
    if (dst != NULL) {
        NSMutableData *object = (__bridge NSMutableData *)dst;
        [object appendBytes:ptr length:(NSUInteger)len];
    }
}

void cq_objc_int64s_recv(struct cq_int64s *dst, int64_t value) {
    if (dst != NULL) {
        NSMutableArray<NSNumber *> *object = (__bridge NSMutableArray *)dst;
        [object addObject:@(value)];
    }
}

void cq_objc_strings_recv(struct cq_strings *dst, const char *value) {
    if (dst && value) {
        NSMutableArray<NSString *> *object = (__bridge NSMutableArray *)dst;
        [object addObject:@(value)];
    }
}

void cq_objc_ss_map_recv(struct cq_ss_map *dst, const char *key, const char *value) {
    if (dst && key && value) {
        NSMutableDictionary<NSString *, NSString *> *object = (__bridge NSMutableDictionary *)dst;
        [object setObject:@(value) forKey:@(key)];
    }
}

void cq_objc_bytes_send(struct cq_bytes *src, cq_bytes_recv recv, struct cq_bytes *dst) {
    if (src && recv) {
        NSData *object = (__bridge NSData *)src;
        recv(dst, object.bytes, (int32_t)object.length);
    }
}

void cq_objc_int64s_send(struct cq_int64s *src, cq_int64s_recv recv, struct cq_int64s *dst) {
    if (src && recv) {
        NSArray<NSNumber *> *object = (__bridge NSArray *)src;
        for (NSNumber *it in object) {
            recv(dst, it.longLongValue);
        }
    }
}

void cq_objc_strings_send(struct cq_strings *src, cq_strings_recv recv, struct cq_strings *dst) {
    if (src && recv) {
        NSArray<NSString *> *object = (__bridge NSArray *)src;
        for (NSString *it in object) {
            recv(dst, it.UTF8String);
        }
    }
}

void cq_objc_ss_map_send(struct cq_ss_map *src, cq_ss_map_recv recv, struct cq_ss_map *dst) {
    if (src && recv) {
        NSDictionary<NSString *, NSString *> *object = (__bridge NSDictionary *)src;
        for (NSString *key in object) {
            recv(dst, key.UTF8String, object[key].UTF8String);
        }
    }
}

NSData *CQDataFrom(cq_bytes_send send, struct cq_bytes *src) {
    NSMutableData *object = nil;
    if (send) {
        object = [NSMutableData data];
        send(src, cq_objc_bytes_recv, cq_objc_mut_bytes(object));
    }
    return object;
}

NSArray<NSNumber *> *CQInt64sFrom(cq_int64s_send send, struct cq_int64s *src) {
    NSMutableArray<NSNumber *> *object = nil;
    if (send) {
        object = [NSMutableArray array];
        send(src, cq_objc_int64s_recv, cq_objc_int64s(object));
    }
    return object;
}

NSArray<NSString *> *CQStringsFrom(cq_strings_send send, struct cq_strings *src) {
    NSMutableArray<NSString *> *object = nil;
    if (send) {
        object = [NSMutableArray array];
        send(src, cq_objc_strings_recv, cq_objc_strings(object));
    }
    return object;
}

NSDictionary<NSString *, NSString *> *CQSSMapFrom(cq_ss_map_send send, struct cq_ss_map *src) {
    NSMutableDictionary<NSString *, NSString *> *object = nil;
    if (send) {
        object = [NSMutableDictionary dictionary];
        send(src, cq_objc_ss_map_recv, cq_objc_ss_map(object));
    }
    return object;
}

void CQSendBytes(NSData *src, cq_bytes_recv recv, struct cq_bytes *dst) {
    cq_objc_bytes_send(cq_objc_bytes(src), recv, dst);
}

void CQSendInt64s(NSArray<NSNumber *> *src, cq_int64s_recv recv, struct cq_int64s *dst) {
    cq_objc_int64s_send(cq_objc_int64s(src), recv, dst);
}

void CQSendStrings(NSArray<NSString *> *src, cq_strings_recv recv, struct cq_strings *dst) {
    cq_objc_strings_send(cq_objc_strings(src), recv, dst);
}

void CQSendSSMap(NSDictionary<NSString *, NSString *> *src, cq_ss_map_recv recv, struct cq_ss_map *dst) {
    cq_objc_ss_map_send(cq_objc_ss_map(src), recv, dst);
}

struct cq_bytes *CQStoreBytes(NSData *object) {
    return cq_store_bytes(cq_objc_bytes_send, cq_objc_bytes(object));
}

struct cq_int64s *CQStoreInt64s(NSArray<NSNumber *> *object) {
    return cq_store_int64s(cq_objc_int64s_send, cq_objc_int64s(object));
}

struct cq_strings *CQStoreStrings(NSArray<NSString *> *object) {
    return cq_store_strings(cq_objc_strings_send, cq_objc_strings(object));
}

struct cq_ss_map *CQStoreSSMap(NSDictionary<NSString *, NSString *> *object) {
    return cq_store_ss_map(cq_objc_ss_map_send, cq_objc_ss_map(object));
}
