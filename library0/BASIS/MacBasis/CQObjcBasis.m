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

NSString *CQNullableString(const char *s) {return s ? @(s) : nil;}
NSString *CQNonnullString (const char *s) {return s ? @(s) : @"";}

//interfaces for interaction with c:

static void bytes_out(void *dst, const void *ptr, int32_t len) {
    if (dst == NULL) {
        return;
    }
    NSMutableData *object = (__bridge NSMutableData *)dst;
    if (ptr && len > 0) {
        [object appendBytes:ptr length:(NSUInteger)len];
    }
}

static void i64_list_out(void *dst, int64_t value) {
    if (dst == NULL) {
        return;
    }
    NSMutableArray<NSNumber *> *object = (__bridge NSMutableArray *)dst;
    [object addObject:@(value)];
}

static void str_list_out(void *dst, const char *value) {
    if (dst == NULL) {
        return;
    }
    NSMutableArray<NSString *> *object = (__bridge NSMutableArray *)dst;
    [object addObject:CQNonnullString(value)];
}

static void ss_map_out(void *dst, const char *key, const char *value) {
    if (dst == NULL) {
        return;
    }
    NSMutableDictionary<NSString *, NSString *> *object = (__bridge NSMutableDictionary *)dst;
    if (!cq_str_empty(key)) {
        object[@(key)] = CQNonnullString(value);
    }
}

#define GEN_OUT_FN(FN, PARAM, ...)\
/**/    static _Thread_local void *FN##_dst_0 = NULL;\
/**/    static _Thread_local void *FN##_dst_1 = NULL;\
/**/    static _Thread_local void *FN##_dst_2 = NULL;\
/**/    static _Thread_local void *FN##_dst_3 = NULL;\
/**/    static void FN##_0 PARAM {FN(FN##_dst_0, __VA_ARGS__);}\
/**/    static void FN##_1 PARAM {FN(FN##_dst_1, __VA_ARGS__);}\
/**/    static void FN##_2 PARAM {FN(FN##_dst_2, __VA_ARGS__);}\
/**/    static void FN##_3 PARAM {FN(FN##_dst_3, __VA_ARGS__);}

GEN_OUT_FN(bytes_out   , (const void *p, int32_t     n), p, n)
GEN_OUT_FN(i64_list_out, (int64_t     i               ), i   )
GEN_OUT_FN(str_list_out, (const char *i               ), i   )
GEN_OUT_FN(ss_map_out  , (const char *k, const char *v), k, v)

#define RET_OUT_FN(FN, VALUE)\
/**/    static _Thread_local int32_t n = 0;\
/**/    n = (n + 1) % 4;\
/**/    switch (n) {\
/**/        case  0: FN##_dst_0 = VALUE; return FN##_0;\
/**/        case  1: FN##_dst_1 = VALUE; return FN##_1;\
/**/        case  2: FN##_dst_2 = VALUE; return FN##_2;\
/**/        default: FN##_dst_3 = VALUE; return FN##_3;\
/**/    }

cq_bytes_out    cq_oc_bytes_out   (NSMutableData                               *v) {RET_OUT_FN(bytes_out   , (__bridge void *)v);}
cq_i64_list_out cq_oc_i64_list_out(NSMutableArray<NSNumber *>                  *v) {RET_OUT_FN(i64_list_out, (__bridge void *)v);}
cq_str_list_out cq_oc_str_list_out(NSMutableArray<NSString *>                  *v) {RET_OUT_FN(str_list_out, (__bridge void *)v);}
cq_ss_map_out   cq_oc_ss_map_out  (NSMutableDictionary<NSString *, NSString *> *v) {RET_OUT_FN(ss_map_out  , (__bridge void *)v);}

static void bytes_in(void *src, cq_bytes_out out) {
    if (src == 0) {
        return;
    }
    NSData *object = (__bridge NSData *)src;
    if (out != NULL) {
        out(object.bytes, (int32_t)object.length);
    }
}

static void i64_list_in(void *src, cq_i64_list_out out) {
    if (src == 0) {
        return;
    }
    NSArray<NSNumber *> *object = (__bridge NSArray *)src;
    if (out != NULL) {
        for (NSNumber *it in object) {
            out((int64_t)it.longLongValue);
        }
    }
}

static void str_list_in(void *src, cq_str_list_out out) {
    if (src == 0) {
        return;
    }
    NSArray<NSString *> *object = (__bridge NSArray *)src;
    if (out != NULL) {
        for (NSString *it in object) {
            out(it.UTF8String);
        }
    }
}

static void ss_map_in(void *src, cq_ss_map_out out) {
    if (src == 0) {
        return;
    }
    NSDictionary<NSString *, NSString *> *object = (__bridge NSDictionary *)src;
    if (out != NULL) {
        for (NSString *key in object) {
            out(key.UTF8String, object[key].UTF8String);
        }
    }
}

#define GEN_IN_FN(FN, PARAM, ...)\
/**/    static _Thread_local void *FN##_src_0 = 0;\
/**/    static _Thread_local void *FN##_src_1 = 0;\
/**/    static _Thread_local void *FN##_src_2 = 0;\
/**/    static _Thread_local void *FN##_src_3 = 0;\
/**/    static void FN##_0 PARAM {FN(FN##_src_0, __VA_ARGS__);}\
/**/    static void FN##_1 PARAM {FN(FN##_src_1, __VA_ARGS__);}\
/**/    static void FN##_2 PARAM {FN(FN##_src_2, __VA_ARGS__);}\
/**/    static void FN##_3 PARAM {FN(FN##_src_3, __VA_ARGS__);}

GEN_IN_FN(bytes_in   , (cq_bytes_out    out), out)
GEN_IN_FN(i64_list_in, (cq_i64_list_out out), out)
GEN_IN_FN(str_list_in, (cq_str_list_out out), out)
GEN_IN_FN(ss_map_in  , (cq_ss_map_out   out), out)

#define RET_IN_FN(FN, VALUE)\
/**/    static _Thread_local int32_t n = 0;\
/**/    n = (n + 1) % 4;\
/**/    switch (n) {\
/**/        case  0: FN##_src_0 = VALUE; return FN##_0;\
/**/        case  1: FN##_src_1 = VALUE; return FN##_1;\
/**/        case  2: FN##_src_2 = VALUE; return FN##_2;\
/**/        default: FN##_src_3 = VALUE; return FN##_3;\
/**/    }

cq_bytes_in    cq_oc_bytes_in   (NSData                               *v) {RET_IN_FN(bytes_in   , (__bridge void *)v)}
cq_i64_list_in cq_oc_i64_list_in(NSArray<NSNumber *>                  *v) {RET_IN_FN(i64_list_in, (__bridge void *)v)}
cq_str_list_in cq_oc_str_list_in(NSArray<NSString *>                  *v) {RET_IN_FN(str_list_in, (__bridge void *)v)}
cq_ss_map_in   cq_oc_ss_map_in  (NSDictionary<NSString *, NSString *> *v) {RET_IN_FN(ss_map_in  , (__bridge void *)v)}

NSData *cq_oc_bytes(cq_bytes_in in) {
    NSMutableData *object = nil;
    if (in != NULL) {
        object = [NSMutableData data];
        in(cq_oc_bytes_out(object));
    }
    return object;
}

NSArray<NSNumber *> *cq_oc_i64_list(cq_i64_list_in in) {
    NSMutableArray<NSNumber *> *object = nil;
    if (in != NULL) {
        object = [NSMutableArray array];
        in(cq_oc_i64_list_out(object));
    }
    return object;
}

NSArray<NSString *> *cq_oc_str_list(cq_str_list_in in) {
    NSMutableArray<NSString *> *object = nil;
    if (in != NULL) {
        object = [NSMutableArray array];
        in(cq_oc_str_list_out(object));
    }
    return object;
}

NSDictionary<NSString *, NSString *> *cq_oc_ss_map(cq_ss_map_in in) {
    NSMutableDictionary<NSString *, NSString *> *object = nil;
    if (in != NULL) {
        object = [NSMutableDictionary dictionary];
        in(cq_oc_ss_map_out(object));
    }
    return object;
}

void cq_oc_set_bytes   (NSData                               *v, cq_bytes_out    f) {if (v && f) cq_oc_bytes_in   (v)(f);}
void cq_oc_set_i64_list(NSArray<NSNumber *>                  *v, cq_i64_list_out f) {if (v && f) cq_oc_i64_list_in(v)(f);}
void cq_oc_set_str_list(NSArray<NSString *>                  *v, cq_str_list_out f) {if (v && f) cq_oc_str_list_in(v)(f);}
void cq_oc_set_ss_map  (NSDictionary<NSString *, NSString *> *v, cq_ss_map_out   f) {if (v && f) cq_oc_ss_map_in  (v)(f);}

//oc block:

static void run_block(void *raw) {
    if (raw != NULL) {
        void (^block)(void) = (__bridge_transfer id)CFRetain(raw);
        block();
    }
}

static void del_block(void *raw) {
    if (raw != NULL) {
        CFRelease((CFTypeRef)raw);
    }
}

cq_block *cq_block_retain_oc(void (^block)(void)) {
    if (block != nil) {
        CFTypeRef raw = CFRetain((__bridge CFTypeRef)block);
        return cq_block_retain_raw((void *)raw, run_block, del_block);
    }
    return NULL;
}

//bridged oc object:

static const int32_t OBJC_OBJECT_MAGIC = 0x4F424A43; //"OBJC".

static void del_bridge(void *raw) {
    if (raw != NULL) {
        CFRelease((CFTypeRef)raw);
    }
}

cq_bridge *cq_bridge_retain_oc(id object, NSString *cls) {
    if (object != nil) {
        CFTypeRef raw = CFRetain((__bridge CFTypeRef)object);
        return cq_bridge_retain_raw((void *)raw, cls.UTF8String, OBJC_OBJECT_MAGIC, del_bridge);
    }
    return NULL;
}

id cq_bridge_oc(cq_bridge *bridge, Class cls) {
    if (bridge == NULL) {
        return nil;
    }
    
    if (cq_bridge_magic(bridge) != OBJC_OBJECT_MAGIC) {
        //it's not a objc object.
        return nil;
    }
    
    CFTypeRef raw = (CFTypeRef)cq_bridge_raw(bridge);
    NSObject *object = (__bridge_transfer id)CFRetain(raw);
    if (cls && object.class != cls) {
        //it's not a wanted class.
        return nil;
    }
    
    return object;
}
