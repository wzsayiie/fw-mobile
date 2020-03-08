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

#define BYTES    NSData
#define INT_LIST NSArray<NSNumber *>
#define STR_LIST NSArray<NSString *>
#define SS_MAP   NSDictionary<NSString *, NSString *>

#define M_BYTES    NSMutableData
#define M_INT_LIST NSMutableArray<NSNumber *>
#define M_STR_LIST NSMutableArray<NSString *>
#define M_SS_MAP   NSMutableDictionary<NSString *, NSString *>

static _Thread_local CFTypeRef _dst_bytes    = NULL;
static _Thread_local CFTypeRef _dst_int_list = NULL;
static _Thread_local CFTypeRef _dst_str_list = NULL;
static _Thread_local CFTypeRef _dst_ss_map   = NULL;

static void bytes_out(const void *bytes, int32_t len) {
    if (_dst_bytes != NULL) {
        M_BYTES *object = (__bridge M_BYTES *)_dst_bytes;
        
        if (bytes && len > 0) {
            [object setData:[NSData dataWithBytes:bytes length:len]];
        } else {
            [object setLength:0];
        }
    }
}

static void int_list_out(int64_t item) {
    if (_dst_int_list != NULL) {
        M_INT_LIST *object = (__bridge M_INT_LIST *)_dst_int_list;
        [object addObject:@(item)];
    }
}

static void str_list_out(const char *item) {
    if (_dst_str_list != NULL) {
        M_STR_LIST *object = (__bridge M_STR_LIST *)_dst_str_list;
        [object addObject:CQNonnullString(item)];
    }
}

static void ss_map_out(const char *key, const char *value) {
    if (_dst_ss_map && !cq_str_empty(key)) {
        M_SS_MAP *object = (__bridge M_SS_MAP *)_dst_ss_map;
        object[@(key)] = CQNonnullString(value);
    }
}

static _Thread_local CFTypeRef _src_bytes    = NULL;
static _Thread_local CFTypeRef _src_int_list = NULL;
static _Thread_local CFTypeRef _src_str_list = NULL;
static _Thread_local CFTypeRef _src_ss_map   = NULL;

static void bytes_in(cq_bytes_out out) {
    if (!_src_bytes && !out) {
        return;
    }
    BYTES *object = (__bridge BYTES *)_src_bytes;
    out(object.bytes, (int32_t)object.length);
}

static void int_list_in(cq_i64_list_out out) {
    if (!_src_int_list && !out) {
        return;
    }
    INT_LIST *object = (__bridge INT_LIST *)_src_int_list;
    for (NSNumber *it in object) {
        out((int64_t)it.longLongValue);
    }
}

static void str_list_in(cq_str_list_out out) {
    if (!_src_str_list && !out) {
        return;
    }
    STR_LIST *object = (__bridge STR_LIST *)_src_str_list;
    for (NSString *it in object) {
        out(it.UTF8String);
    }
}

static void ss_map_in(cq_ss_map_out out) {
    if (!_src_ss_map && !out) {
        return;
    }
    SS_MAP *object = (__bridge SS_MAP *)_src_ss_map;
    for (NSString *key in object) {
        out(key.UTF8String, object[key].UTF8String);
    }
}

cq_bytes_out    cq_oc_bytes_out   (M_BYTES    *a) {_dst_bytes    = (__bridge CFTypeRef)a; return bytes_out   ;}
cq_i64_list_out cq_oc_i64_list_out(M_INT_LIST *a) {_dst_int_list = (__bridge CFTypeRef)a; return int_list_out;}
cq_str_list_out cq_oc_str_list_out(M_STR_LIST *a) {_dst_str_list = (__bridge CFTypeRef)a; return str_list_out;}
cq_ss_map_out   cq_oc_ss_map_out  (M_SS_MAP   *a) {_dst_ss_map   = (__bridge CFTypeRef)a; return ss_map_out  ;}

cq_bytes_in    cq_oc_bytes_in   (BYTES    *a) {_src_bytes    = (__bridge CFTypeRef)a; return bytes_in   ;}
cq_i64_list_in cq_oc_i64_list_in(INT_LIST *a) {_src_int_list = (__bridge CFTypeRef)a; return int_list_in;}
cq_str_list_in cq_oc_str_list_in(STR_LIST *a) {_src_str_list = (__bridge CFTypeRef)a; return str_list_in;}
cq_ss_map_in   cq_oc_ss_map_in  (SS_MAP   *a) {_src_ss_map   = (__bridge CFTypeRef)a; return ss_map_in  ;}

#define KEEP(VALUE, CODE)\
/**/    do{\
/**/        typeof(VALUE) __last = VALUE;\
/**/        CODE\
/**/        VALUE = __last;\
/**/    } while (0)

BYTES *cq_oc_bytes_from(cq_bytes_in in) {
    if (in == NULL) {
        return nil;
    }
    
    M_BYTES *object = [NSMutableData data];
    //NOTE: hold last value of _dst_bytes.
    //the function shouldn't affect last cq_oc_bytes_out() call.
    KEEP(_dst_bytes, {
        in(cq_oc_bytes_out(object));
    });
    return object;
}

INT_LIST *cq_oc_i64_list_from(cq_i64_list_in in) {
    if (in == NULL) {
        return nil;
    }
    
    M_INT_LIST *object = [NSMutableArray array];
    KEEP(_dst_int_list, {
        in(cq_oc_i64_list_out(object));
    });
    return object;
}

STR_LIST *cq_oc_str_list_from(cq_str_list_in in) {
    if (in == NULL) {
        return nil;
    }
    
    M_STR_LIST *object = [NSMutableArray array];
    KEEP(_dst_str_list, {
        in(cq_oc_str_list_out(object));
    });
    return object;
}

SS_MAP *cq_oc_ss_map_from(cq_ss_map_in in) {
    if (in == NULL) {
        return nil;
    }
    
    M_SS_MAP *object = [NSMutableDictionary dictionary];
    KEEP(_dst_ss_map, {
        in(cq_oc_ss_map_out(object));
    });
    return object;
}

void cq_oc_bytes_assign(BYTES *object, cq_bytes_out out) {
    KEEP(_src_bytes, {
        cq_oc_bytes_in(object)(out);
    });
}

void cq_oc_i64_list_assign(INT_LIST *object, cq_i64_list_out out) {
    KEEP(_src_int_list, {
        cq_oc_i64_list_in(object)(out);
    });
}

void cq_oc_str_list_assign(STR_LIST *object, cq_str_list_out out) {
    KEEP(_src_str_list, {
        cq_oc_str_list_in(object)(out);
    });
}

void cq_oc_ss_map_assign(SS_MAP *object, cq_ss_map_out out) {
    KEEP(_src_ss_map, {
        cq_oc_ss_map_in(object)(out);
    });
}

//object reference:

static const int32_t ObjcObjectMagic = 0x4F424A43; //"OBJC".

static void release_raw_oc(void *raw) {
    if (raw != NULL) {
        CFRelease((CFTypeRef)raw);
    }
}

cq_obj *cq_retain_oc_obj(NSObject *object, NSString *cls) {
    if (object == nil) {
        return NULL;
    }
    
    CFTypeRef raw = CFRetain((__bridge CFTypeRef)object);
    cq_obj *ptr = cq_retain_raw_obj((void *)raw, release_raw_oc);
    
    if (cls.length > 0) {
        cq_set_obj_cls(ptr, cls.UTF8String);
    }
    cq_set_obj_magic(ptr, ObjcObjectMagic);
    
    return ptr;
}

NSObject *cq_obj_raw_oc(cq_obj *ptr, Class cls) {
    if (ptr == NULL) {
        return nil;
    }
    
    if (cq_obj_magic(ptr) != ObjcObjectMagic) {
        //it's not a objc object.
        return nil;
    }
    
    CFTypeRef raw = (CFTypeRef)cq_obj_raw(ptr);
    NSObject *object = (__bridge_transfer NSObject *)CFRetain(raw);
    if (cls && object.class != cls) {
        //it's not a wanted class.
        return nil;
    }
    
    return object;
}
