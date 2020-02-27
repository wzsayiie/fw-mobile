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

cq_bytes   *cq_bytes_cast_mut_oc  (NSMutableData                                *a) {return (__bridge cq_bytes   *)a;}
cq_int64s  *cq_int64s_cast_mut_oc (NSMutableArray<NSNumber *>                   *a) {return (__bridge cq_int64s  *)a;}
cq_strings *cq_strings_cast_mut_oc(NSMutableArray<NSString *>                   *a) {return (__bridge cq_strings *)a;}
cq_ss_map  *cq_ss_map_cast_mut_oc (NSMutableDictionary<NSString *, NSString *>  *a) {return (__bridge cq_ss_map  *)a;}

cq_bytes   *cq_bytes_cast_oc  (NSData                                *a) {return (__bridge cq_bytes   *)a;}
cq_int64s  *cq_int64s_cast_oc (NSArray<NSNumber *>                   *a) {return (__bridge cq_int64s  *)a;}
cq_strings *cq_strings_cast_oc(NSArray<NSString *>                   *a) {return (__bridge cq_strings *)a;}
cq_ss_map  *cq_ss_map_cast_oc (NSDictionary<NSString *, NSString *>  *a) {return (__bridge cq_ss_map  *)a;}

void cq_oc_bytes_receiver(cq_bytes *dst, const void *ptr, int32_t len) {
    if (dst != NULL) {
        NSMutableData *object = (__bridge NSMutableData *)dst;
        [object appendBytes:ptr length:(NSUInteger)len];
    }
}

void cq_oc_int64s_receiver(cq_int64s *dst, int64_t value) {
    if (dst != NULL) {
        NSMutableArray<NSNumber *> *object = (__bridge NSMutableArray *)dst;
        [object addObject:@(value)];
    }
}

void cq_oc_strings_receiver(cq_strings *dst, const char *value) {
    if (dst && value) {
        NSMutableArray<NSString *> *object = (__bridge NSMutableArray *)dst;
        [object addObject:@(value)];
    }
}

void cq_oc_ss_map_receiver(cq_ss_map *dst, const char *key, const char *value) {
    if (dst && key && value) {
        NSMutableDictionary<NSString *, NSString *> *object = (__bridge NSMutableDictionary *)dst;
        [object setObject:@(value) forKey:@(key)];
    }
}

void cq_oc_bytes_sender(cq_bytes *src, cq_bytes_receiver recv, cq_bytes *dst) {
    if (src && recv) {
        NSData *object = (__bridge NSData *)src;
        recv(dst, object.bytes, (int32_t)object.length);
    }
}

void cq_oc_int64s_sender(cq_int64s *src, cq_int64s_receiver recv, cq_int64s *dst) {
    if (src && recv) {
        NSArray<NSNumber *> *object = (__bridge NSArray *)src;
        for (NSNumber *it in object) {
            recv(dst, it.longLongValue);
        }
    }
}

void cq_oc_strings_sender(cq_strings *src, cq_strings_receiver recv, cq_strings *dst) {
    if (src && recv) {
        NSArray<NSString *> *object = (__bridge NSArray *)src;
        for (NSString *it in object) {
            recv(dst, it.UTF8String);
        }
    }
}

void cq_oc_ss_map_sender(cq_ss_map *src, cq_ss_map_receiver recv, cq_ss_map *dst) {
    if (src && recv) {
        NSDictionary<NSString *, NSString *> *object = (__bridge NSDictionary *)src;
        for (NSString *key in object) {
            recv(dst, key.UTF8String, object[key].UTF8String);
        }
    }
}

NSData *cq_oc_bytes_from(cq_bytes_sender send, cq_bytes *src) {
    NSMutableData *object = nil;
    if (send) {
        object = [NSMutableData data];
        send(src, cq_oc_bytes_receiver, cq_bytes_cast_mut_oc(object));
    }
    return object;
}

NSArray<NSNumber *> *cq_oc_int64s_from(cq_int64s_sender send, cq_int64s *src) {
    NSMutableArray<NSNumber *> *object = nil;
    if (send) {
        object = [NSMutableArray array];
        send(src, cq_oc_int64s_receiver, cq_int64s_cast_mut_oc(object));
    }
    return object;
}

NSArray<NSString *> *cq_oc_strings_from(cq_strings_sender send, cq_strings *src) {
    NSMutableArray<NSString *> *object = nil;
    if (send) {
        object = [NSMutableArray array];
        send(src, cq_oc_strings_receiver, cq_strings_cast_mut_oc(object));
    }
    return object;
}

NSDictionary<NSString *, NSString *> *cq_oc_ss_map_from(cq_ss_map_sender send, cq_ss_map *src) {
    NSMutableDictionary<NSString *, NSString *> *object = nil;
    if (send) {
        object = [NSMutableDictionary dictionary];
        send(src, cq_oc_ss_map_receiver, cq_ss_map_cast_mut_oc(object));
    }
    return object;
}

void cq_send_oc_bytes(NSData *src, cq_bytes_receiver recv, cq_bytes *dst) {
    cq_oc_bytes_sender(cq_bytes_cast_oc(src), recv, dst);
}

void cq_send_oc_int64s(NSArray<NSNumber *> *src, cq_int64s_receiver recv, cq_int64s *dst) {
    cq_oc_int64s_sender(cq_int64s_cast_oc(src), recv, dst);
}

void cq_send_oc_strings(NSArray<NSString *> *src, cq_strings_receiver recv, cq_strings *dst) {
    cq_oc_strings_sender(cq_strings_cast_oc(src), recv, dst);
}

void cq_send_oc_ss_map(NSDictionary<NSString *, NSString *> *src, cq_ss_map_receiver recv, cq_ss_map *dst) {
    cq_oc_ss_map_sender(cq_ss_map_cast_oc(src), recv, dst);
}

cq_bytes *cq_store_oc_bytes(NSData *object) {
    return cq_store_c_bytes(cq_oc_bytes_sender, cq_bytes_cast_oc(object));
}

cq_int64s *cq_store_oc_int64s(NSArray<NSNumber *> *object) {
    return cq_store_c_int64s(cq_oc_int64s_sender, cq_int64s_cast_oc(object));
}

cq_strings *cq_store_oc_strings(NSArray<NSString *> *object) {
    return cq_store_c_strings(cq_oc_strings_sender, cq_strings_cast_oc(object));
}

cq_ss_map *cq_store_oc_ss_map(NSDictionary<NSString *, NSString *> *object) {
    return cq_store_c_ss_map(cq_oc_ss_map_sender, cq_ss_map_cast_oc(object));
}
