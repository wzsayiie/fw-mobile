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

static void bool_out  (void *dst, bool    value) {if (dst) *(BOOL    *)dst = value;}
static void int8_out  (void *dst, int8_t  value) {if (dst) *(int8_t  *)dst = value;}
static void int16_out (void *dst, int16_t value) {if (dst) *(int16_t *)dst = value;}
static void int32_out (void *dst, int32_t value) {if (dst) *(int32_t *)dst = value;}
static void int64_out (void *dst, int64_t value) {if (dst) *(int64_t *)dst = value;}
static void float_out (void *dst, float   value) {if (dst) *(float   *)dst = value;}
static void double_out(void *dst, double  value) {if (dst) *(double  *)dst = value;}

static void str_out(void *dst, const char *str) {
    if (dst == NULL) {
        return;
    }
    NSMutableString *object = (__bridge NSMutableString *)dst;
    [object setString:CQNonnullString(str)];
}

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

GEN_OUT_FN(bool_out  , (bool    v), v)
GEN_OUT_FN(int8_out  , (int8_t  v), v)
GEN_OUT_FN(int16_out , (int16_t v), v)
GEN_OUT_FN(int32_out , (int32_t v), v)
GEN_OUT_FN(int64_out , (int64_t v), v)
GEN_OUT_FN(float_out , (float   v), v)
GEN_OUT_FN(double_out, (double  v), v)

GEN_OUT_FN(str_out     , (const char *s               ), s   )
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

cq_bool_out   cq_oc_bool_out  (BOOL    *value) {RET_OUT_FN(bool_out  , value);}
cq_int8_out   cq_oc_int8_out  (int8_t  *value) {RET_OUT_FN(int8_out  , value);}
cq_int16_out  cq_oc_int16_out (int16_t *value) {RET_OUT_FN(int16_out , value);}
cq_int32_out  cq_oc_int32_out (int32_t *value) {RET_OUT_FN(int32_out , value);}
cq_int64_out  cq_oc_int64_out (int64_t *value) {RET_OUT_FN(int64_out , value);}
cq_float_out  cq_oc_float_out (float   *value) {RET_OUT_FN(float_out , value);}
cq_double_out cq_oc_double_out(double  *value) {RET_OUT_FN(double_out, value);}

cq_str_out      cq_oc_str_out     (NSMutableString                             *v) {RET_OUT_FN(str_out     , (__bridge void *)v);}
cq_bytes_out    cq_oc_bytes_out   (NSMutableData                               *v) {RET_OUT_FN(bytes_out   , (__bridge void *)v);}
cq_i64_list_out cq_oc_i64_list_out(NSMutableArray<NSNumber *>                  *v) {RET_OUT_FN(i64_list_out, (__bridge void *)v);}
cq_str_list_out cq_oc_str_list_out(NSMutableArray<NSString *>                  *v) {RET_OUT_FN(str_list_out, (__bridge void *)v);}
cq_ss_map_out   cq_oc_ss_map_out  (NSMutableDictionary<NSString *, NSString *> *v) {RET_OUT_FN(ss_map_out  , (__bridge void *)v);}

static void bool_in  (intmax_t src, cq_bool_out   out) {if (out) out(*(BOOL    *)&src);}
static void int8_in  (intmax_t src, cq_int8_out   out) {if (out) out(*(int8_t  *)&src);}
static void int16_in (intmax_t src, cq_int16_out  out) {if (out) out(*(int16_t *)&src);}
static void int32_in (intmax_t src, cq_int32_out  out) {if (out) out(*(int32_t *)&src);}
static void int64_in (intmax_t src, cq_int64_out  out) {if (out) out(*(int64_t *)&src);}
static void float_in (intmax_t src, cq_float_out  out) {if (out) out(*(float   *)&src);}
static void double_in(intmax_t src, cq_double_out out) {if (out) out(*(double  *)&src);}

static void str_in(intmax_t src, cq_str_out out) {
    if (src == 0) {
        return;
    }
    NSString *object = (__bridge NSString *) *(void **)&src;
    if (out != NULL) {
        out(object.UTF8String);
    }
}

static void bytes_in(intmax_t src, cq_bytes_out out) {
    if (src == 0) {
        return;
    }
    NSData *object = (__bridge NSData *) *(void **)&src;
    if (out != NULL) {
        out(object.bytes, (int32_t)object.length);
    }
}

static void i64_list_in(intmax_t src, cq_i64_list_out out) {
    if (src == 0) {
        return;
    }
    NSArray<NSNumber *> *object = (__bridge NSArray *) *(void **)&src;
    if (out != NULL) {
        for (NSNumber *it in object) {
            out((int64_t)it.longLongValue);
        }
    }
}

static void str_list_in(intmax_t src, cq_str_list_out out) {
    if (src == 0) {
        return;
    }
    NSArray<NSString *> *object = (__bridge NSArray *) *(void **)&src;
    if (out != NULL) {
        for (NSString *it in object) {
            out(it.UTF8String);
        }
    }
}

static void ss_map_in(intmax_t src, cq_ss_map_out out) {
    if (src == 0) {
        return;
    }
    NSDictionary<NSString *, NSString *> *object = (__bridge NSDictionary *) *(void **)&src;
    if (out != NULL) {
        for (NSString *key in object) {
            out(key.UTF8String, object[key].UTF8String);
        }
    }
}

#define GEN_IN_FN(FN, PARAM, ...)\
/**/    static _Thread_local intmax_t FN##_src_0 = 0;\
/**/    static _Thread_local intmax_t FN##_src_1 = 0;\
/**/    static _Thread_local intmax_t FN##_src_2 = 0;\
/**/    static _Thread_local intmax_t FN##_src_3 = 0;\
/**/    static void FN##_0 PARAM {FN(FN##_src_0, __VA_ARGS__);}\
/**/    static void FN##_1 PARAM {FN(FN##_src_1, __VA_ARGS__);}\
/**/    static void FN##_2 PARAM {FN(FN##_src_2, __VA_ARGS__);}\
/**/    static void FN##_3 PARAM {FN(FN##_src_3, __VA_ARGS__);}

GEN_IN_FN(bool_in  , (cq_bool_out   out), out)
GEN_IN_FN(int8_in  , (cq_int8_out   out), out)
GEN_IN_FN(int16_in , (cq_int16_out  out), out)
GEN_IN_FN(int32_in , (cq_int32_out  out), out)
GEN_IN_FN(int64_in , (cq_int64_out  out), out)
GEN_IN_FN(float_in , (cq_float_out  out), out)
GEN_IN_FN(double_in, (cq_double_out out), out)

GEN_IN_FN(str_in     , (cq_str_out      out), out)
GEN_IN_FN(bytes_in   , (cq_bytes_out    out), out)
GEN_IN_FN(i64_list_in, (cq_i64_list_out out), out)
GEN_IN_FN(str_list_in, (cq_str_list_out out), out)
GEN_IN_FN(ss_map_in  , (cq_ss_map_out   out), out)

#define RET_IN_FN(FN, TYPE, VALUE)\
/**/    static _Thread_local int32_t n = 0;\
/**/    n = (n + 1) % 4;\
/**/    TYPE cache = VALUE;\
/**/    switch (n) {\
/**/        case  0: FN##_src_0 = *(intmax_t *)&cache; return FN##_0;\
/**/        case  1: FN##_src_1 = *(intmax_t *)&cache; return FN##_1;\
/**/        case  2: FN##_src_2 = *(intmax_t *)&cache; return FN##_2;\
/**/        default: FN##_src_3 = *(intmax_t *)&cache; return FN##_3;\
/**/    }

cq_bool_in   cq_oc_bool_in  (BOOL    v) {RET_IN_FN(bool_in  , BOOL   , v);}
cq_int8_in   cq_oc_int8_in  (int8_t  v) {RET_IN_FN(int8_in  , int8_t , v);}
cq_int16_in  cq_oc_int16_in (int16_t v) {RET_IN_FN(int16_in , int16_t, v);}
cq_int32_in  cq_oc_int32_in (int32_t v) {RET_IN_FN(int32_in , int32_t, v);}
cq_int64_in  cq_oc_int64_in (int64_t v) {RET_IN_FN(int64_in , int64_t, v);}
cq_float_in  cq_oc_float_in (float   v) {RET_IN_FN(float_in , float  , v);}
cq_double_in cq_oc_double_in(double  v) {RET_IN_FN(double_in, double , v);}

cq_str_in      cq_oc_str_in     (NSString                             *v) {RET_IN_FN(str_in     , void *, (__bridge void *)v)}
cq_bytes_in    cq_oc_bytes_in   (NSData                               *v) {RET_IN_FN(bytes_in   , void *, (__bridge void *)v)}
cq_i64_list_in cq_oc_i64_list_in(NSArray<NSNumber *>                  *v) {RET_IN_FN(i64_list_in, void *, (__bridge void *)v)}
cq_str_list_in cq_oc_str_list_in(NSArray<NSString *>                  *v) {RET_IN_FN(str_list_in, void *, (__bridge void *)v)}
cq_ss_map_in   cq_oc_ss_map_in  (NSDictionary<NSString *, NSString *> *v) {RET_IN_FN(ss_map_in  , void *, (__bridge void *)v)}

BOOL    cq_oc_bool  (cq_bool_in   in) {BOOL    r = 0; if (in) in(cq_oc_bool_out  (&r)); return r;}
int8_t  cq_oc_int8  (cq_int8_in   in) {int8_t  r = 0; if (in) in(cq_oc_int8_out  (&r)); return r;}
int16_t cq_oc_int16 (cq_int16_in  in) {int16_t r = 0; if (in) in(cq_oc_int16_out (&r)); return r;}
int32_t cq_oc_int32 (cq_int32_in  in) {int32_t r = 0; if (in) in(cq_oc_int32_out (&r)); return r;}
int64_t cq_oc_int64 (cq_int64_in  in) {int64_t r = 0; if (in) in(cq_oc_int64_out (&r)); return r;}
float   cq_oc_float (cq_float_in  in) {float   r = 0; if (in) in(cq_oc_float_out (&r)); return r;}
double  cq_oc_double(cq_double_in in) {double  r = 0; if (in) in(cq_oc_double_out(&r)); return r;}

NSString *cq_oc_str(cq_str_in in) {
    NSMutableString *object = nil;
    if (in != NULL) {
        object = [NSMutableString string];
        in(cq_oc_str_out(object));
    }
    return object;
}

NSData *cq_oc_data(cq_bytes_in in) {
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

void cq_oc_set_bool  (BOOL    value, cq_bool_out   out) {if (out) out(value);}
void cq_oc_set_int8  (int8_t  value, cq_int8_out   out) {if (out) out(value);}
void cq_oc_set_int16 (int16_t value, cq_int16_out  out) {if (out) out(value);}
void cq_oc_set_int32 (int32_t value, cq_int32_out  out) {if (out) out(value);}
void cq_oc_set_int64 (int64_t value, cq_int64_out  out) {if (out) out(value);}
void cq_oc_set_float (float   value, cq_float_out  out) {if (out) out(value);}
void cq_oc_set_double(double  value, cq_double_out out) {if (out) out(value);}

void cq_oc_set_str     (NSString                             *v, cq_str_out      f) {if (v && f) cq_oc_str_in     (v)(f);}
void cq_oc_set_bytes   (NSData                               *v, cq_bytes_out    f) {if (v && f) cq_oc_bytes_in   (v)(f);}
void cq_oc_set_i64_list(NSArray<NSNumber *>                  *v, cq_i64_list_out f) {if (v && f) cq_oc_i64_list_in(v)(f);}
void cq_oc_set_str_list(NSArray<NSString *>                  *v, cq_str_list_out f) {if (v && f) cq_oc_str_list_in(v)(f);}
void cq_oc_set_ss_map  (NSDictionary<NSString *, NSString *> *v, cq_ss_map_out   f) {if (v && f) cq_oc_ss_map_in  (v)(f);}

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
