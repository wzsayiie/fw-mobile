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

static void bytes_clear     (void *d) { NSMutableData       *a = (__bridge id)d; [a setLength:0]     ; }
static void int64_list_clear(void *d) { NSMutableArray      *a = (__bridge id)d; [a removeAllObjects]; }
static void str_list_clear  (void *d) { NSMutableArray      *a = (__bridge id)d; [a removeAllObjects]; }
static void ss_map_clear    (void *d) { NSMutableDictionary *a = (__bridge id)d; [a removeAllObjects]; }

static void bytes_recv(void *dst, const void *bytes, int32_t length) {
    NSMutableData *object = (__bridge id)dst;
    
    if (bytes && length > 0) {
        [object appendBytes:bytes length:(NSUInteger)length];
    }
}

static void int64_list_recv(void *dst, int64_t item) {
    NSMutableArray<NSNumber *> *object = (__bridge id)dst;
    
    [object addObject:@(item)];
}

static void str_list_recv(void *dst, const char *item) {
    NSMutableArray<NSString *> *object = (__bridge id)dst;
    
    [object addObject:CQNonnullString(item)];
}

static void ss_map_recv(void *dst, const char *key, const char *value) {
    NSMutableDictionary<NSString *, NSString *> *object = (__bridge id)dst;
    
    if (cq_str_non_empty(key)) {
        object[@(key)] = CQNonnullString(value);
    }
}

static void bytes_send(void *src, cq_bytes *dst) {
    NSData *object = (__bridge id)src;
    
    dst->recv(dst->ref, object.bytes, (int32_t)object.length);
}

static void int64_list_send(void *src, cq_int64_list *dst) {
    NSArray<NSNumber *> *object = (__bridge id)src;
    
    for (NSNumber *it in object) {
        dst->recv(dst->ref, (int64_t)it.longLongValue);
    }
}

static void str_list_send(void *src, cq_str_list *dst) {
    NSArray<NSString *> *object = (__bridge id)src;
    
    for (NSString *it in object) {
        dst->recv(dst->ref, it.UTF8String);
    }
}

static void ss_map_send(void *src, cq_ss_map *dst) {
    NSDictionary<NSString *, NSString *> *object = (__bridge id)src;
    
    for (NSString *key in object) {
        dst->recv(dst->ref, key.UTF8String, object[key].UTF8String);
    }
}

cq_bytes *cq_oc_bytes(NSData *object) {
    if (object == nil) {
        return NULL;
    }
    
    BOOL mutable = [object isKindOfClass:NSMutableData.class];
    
    cq_bytes *ptr = auto_alloc(sizeof(cq_bytes));
    
    ptr->clear = mutable ? bytes_clear : NULL;
    ptr->recv  = mutable ? bytes_recv  : NULL;
    ptr->send  = bytes_send;
    ptr->ref   = (__bridge void *)object;
    
    return ptr;
}

cq_int64_list *cq_oc_int64_list(NSArray<NSNumber *> *object) {
    if (object == nil) {
        return NULL;
    }
    
    BOOL mutable = [object isKindOfClass:NSMutableArray.class];
    
    cq_int64_list *ptr = auto_alloc(sizeof(cq_int64_list));
    
    ptr->clear = mutable ? int64_list_clear : NULL;
    ptr->recv  = mutable ? int64_list_recv  : NULL;
    ptr->send  = int64_list_send;
    ptr->ref   = (__bridge void *)object;
    
    return ptr;
}

cq_str_list *cq_oc_str_list(NSArray<NSString *> *object) {
    if (object == nil) {
        return NULL;
    }
    
    BOOL mutable = [object isKindOfClass:NSMutableArray.class];
    
    cq_str_list *ptr = auto_alloc(sizeof(cq_str_list));
    
    ptr->clear = mutable ? str_list_clear : NULL;
    ptr->recv  = mutable ? str_list_recv  : NULL;
    ptr->send  = str_list_send;
    ptr->ref   = (__bridge void *)object;
    
    return ptr;
}

cq_ss_map *cq_oc_ss_map(NSDictionary<NSString *, NSString *> *object) {
    if (object == nil) {
        return NULL;
    }
    
    BOOL mutable = [object isKindOfClass:NSMutableDictionary.class];
    
    cq_ss_map *ptr = auto_alloc(sizeof(cq_ss_map));
    
    ptr->clear = mutable ? ss_map_clear : NULL;
    ptr->recv  = mutable ? ss_map_recv  : NULL;
    ptr->send  = ss_map_send;
    ptr->ref   = (__bridge void *)object;
    
    return ptr;
}

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
        return cq_block_retain((void *)raw, run_block, del_block);
    }
    return NULL;
}

//bridged oc object:

static const int32_t OBJC_OBJECT_MAGIC = 0x4F424A43; //"OBJC".

static void del_oc_object(void *raw) {
    if (raw != NULL) {
        CFRelease((CFTypeRef)raw);
    }
}

cq_object *cq_object_retain_oc(id object, NSString *cls) {
    if (object != nil) {
        CFTypeRef raw = CFRetain((__bridge CFTypeRef)object);
        return cq_object_retain((void *)raw, cls.UTF8String, OBJC_OBJECT_MAGIC, del_oc_object);
    }
    return NULL;
}

id cq_object_oc(cq_object *object, Class cls) {
    if (object == NULL) {
        return nil;
    }
    
    if (cq_object_magic(object) != OBJC_OBJECT_MAGIC) {
        //it's not a objc object.
        return nil;
    }
    
    CFTypeRef raw = (CFTypeRef)cq_object_raw(object);
    NSObject *ret = (__bridge_transfer id)CFRetain(raw);
    if (cls && ret.class != cls) {
        //it's not a wanted class.
        return nil;
    }
    
    return ret;
}
