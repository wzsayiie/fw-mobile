#import <Foundation/Foundation.h>
#import <objc/runtime.h>
#import "cqcbasis.h"

//property synthesize:

//it's not supported to associate a weak object to the other object.
//OBJC_ASSOCIATION_ASSIGN holds wild pointer possibly.

void CQSetStrongProperty(id object, const void *key, id value);
void CQSetCopyProperty  (id object, const void *key, id value);

id CQGetProperty(id object, const void *key);

#define CQ_SYNTHESIZE_STRONG(GET, SET)\
/**/    - (id)GET {\
/**/        return CQGetProperty(self, @selector(GET));\
/**/    }\
/**/    - (void)SET:(id)value {\
/**/        CQSetStrongProperty(self, @selector(GET), value);\
/**/    }

#define CQ_SYNTHESIZE_COPY(GET, SET)\
/**/    - (id)GET {\
/**/        return CQGetProperty(self, @selector(GET));\
/**/    }\
/**/    - (void)SET:(id)value {\
/**/        CQSetCopyProperty(self, @selector(GET), value);\
/**/    }

//shared singleton:

#define CQ_SHARED_OBJECT(CLASS, OBJECT, CODE)\
/**/    do {\
/**/        static CLASS *OBJECT = nil;\
/**/        static dispatch_once_t token = 0;\
/**/        dispatch_once(&token, ^{\
/**/            OBJECT = [[CLASS alloc] init];\
/**/            CODE\
/**/        });\
/**/        return OBJECT;\
/**/    } while (0)

#define CQ_SHARED_OBJECT_OF_SELF()\
/**/    do {\
/**/        static id object = nil;\
/**/        static dispatch_once_t token = 0;\
/**/        dispatch_once(&token, ^{\
/**/            object = [[self alloc] init];\
/**/        });\
/**/        return object;\
/**/    } while (0)

//string key:

#define CQ_DECLARE_S(string) extern NSString *const string
#define CQ_DEFINE_S(string) NSString *const string = @""#string

//weak object:

#define CQ_WEAK(NAME, VALUE) __weak typeof(VALUE) NAME = VALUE

//cast "const char *" to "NSString *".
NSString *CQNullableString(const char *string);
NSString *CQNonnullString(const char *string);

//data interfaces for interaction with c:

cq_bool_out   cq_oc_bool_out  (BOOL    *value);
cq_int8_out   cq_oc_int8_out  (int8_t  *value);
cq_int16_out  cq_oc_int16_out (int16_t *value);
cq_int32_out  cq_oc_int32_out (int32_t *value);
cq_int64_out  cq_oc_int64_out (int64_t *value);
cq_float_out  cq_oc_float_out (float   *value);
cq_double_out cq_oc_double_out(double  *value);

cq_str_out      cq_oc_str_out     (NSMutableString *value);
cq_bytes_out    cq_oc_bytes_out   (NSMutableData   *value);
cq_i64_list_out cq_oc_i64_list_out(NSMutableArray<NSNumber *> *value);
cq_str_list_out cq_oc_str_list_out(NSMutableArray<NSString *> *value);
cq_ss_map_out   cq_oc_ss_map_out  (NSMutableDictionary<NSString *, NSString *> *value);

cq_bool_in   cq_oc_bool_in  (BOOL    value);
cq_int8_in   cq_oc_int8_in  (int8_t  value);
cq_int16_in  cq_oc_int16_in (int16_t value);
cq_int32_in  cq_oc_int32_in (int32_t value);
cq_int64_in  cq_oc_int64_in (int64_t value);
cq_float_in  cq_oc_float_in (float   value);
cq_double_in cq_oc_double_in(double  value);

cq_str_in      cq_oc_str_in     (NSString *value);
cq_bytes_in    cq_oc_bytes_in   (NSData   *value);
cq_i64_list_in cq_oc_i64_list_in(NSArray<NSNumber *> *value);
cq_str_list_in cq_oc_str_list_in(NSArray<NSString *> *value);
cq_ss_map_in   cq_oc_ss_map_in  (NSDictionary<NSString *, NSString *> *value);

BOOL    cq_oc_bool  (cq_bool_in   in);
int8_t  cq_oc_int8  (cq_int8_in   in);
int16_t cq_oc_int16 (cq_int16_in  in);
int32_t cq_oc_int32 (cq_int32_in  in);
int64_t cq_oc_int64 (cq_int64_in  in);
float   cq_oc_float (cq_float_in  in);
double  cq_oc_double(cq_double_in in);

NSString                             *cq_oc_str     (cq_str_in      in);
NSData                               *cq_oc_data    (cq_bytes_in    in);
NSArray<NSNumber *>                  *cq_oc_i64_list(cq_i64_list_in in);
NSArray<NSString *>                  *cq_oc_str_list(cq_str_list_in in);
NSDictionary<NSString *, NSString *> *cq_oc_ss_map  (cq_ss_map_in   in);

void cq_oc_set_bool  (BOOL    value, cq_bool_out   out);
void cq_oc_set_int8  (int8_t  value, cq_int8_out   out);
void cq_oc_set_int16 (int16_t value, cq_int16_out  out);
void cq_oc_set_int32 (int32_t value, cq_int32_out  out);
void cq_oc_set_int64 (int64_t value, cq_int64_out  out);
void cq_oc_set_float (float   value, cq_float_out  out);
void cq_oc_set_double(double  value, cq_double_out out);

void cq_oc_set_str     (NSString                        *value, cq_str_out      out);
void cq_oc_set_bytes   (NSData                          *value, cq_bytes_out    out);
void cq_oc_set_i64_list(NSArray<NSNumber *>             *value, cq_i64_list_out out);
void cq_oc_set_str_list(NSArray<NSString *>             *value, cq_str_list_out out);
void cq_oc_set_ss_map  (NSDictionary<NSString *, NSString *> *, cq_ss_map_out   out);

//block:

void cq_oc_block_bool_in  (NSString *name, BOOL    value);
void cq_oc_block_int8_in  (NSString *name, int8_t  value);
void cq_oc_block_int16_in (NSString *name, int16_t value);
void cq_oc_block_int32_in (NSString *name, int32_t value);
void cq_oc_block_int64_in (NSString *name, int64_t value);
void cq_oc_block_float_in (NSString *name, float   value);
void cq_oc_block_double_in(NSString *name, double  value);

void cq_oc_block_str_in     (NSString *name, NSString *value);
void cq_oc_block_bytes_in   (NSString *name, NSData   *value);
void cq_oc_block_i64_list_in(NSString *name, NSArray<NSNumber *> *value);
void cq_oc_block_str_list_in(NSString *name, NSArray<NSString *> *value);
void cq_oc_block_ss_map_in  (NSString *name, NSDictionary<NSString *, NSString *> *value);

void cq_oc_block_bool_out  (NSString *name, BOOL    *value);
void cq_oc_block_int8_out  (NSString *name, int8_t  *value);
void cq_oc_block_int16_out (NSString *name, int16_t *value);
void cq_oc_block_int32_out (NSString *name, int32_t *value);
void cq_oc_block_int64_out (NSString *name, int64_t *value);
void cq_oc_block_float_out (NSString *name, float   *value);
void cq_oc_block_double_out(NSString *name, double  *value);

void cq_oc_block_str_out     (NSString *name, NSMutableString *value);
void cq_oc_block_bytes_out   (NSString *name, NSMutableData   *value);
void cq_oc_block_i64_list_out(NSString *name, NSMutableArray<NSNumber *> *value);
void cq_oc_block_str_list_out(NSString *name, NSMutableArray<NSString *> *value);
void cq_oc_block_ss_map_out  (NSString *name, NSMutableDictionary<NSString *, NSString *> *value);

BOOL    cq_oc_block_bool  (NSString *name);
int8_t  cq_oc_block_int8  (NSString *name);
int16_t cq_oc_block_int16 (NSString *name);
int32_t cq_oc_block_int32 (NSString *name);
int64_t cq_oc_block_int64 (NSString *name);
float   cq_oc_block_float (NSString *name);
double  cq_oc_block_double(NSString *name);

NSString                             *cq_oc_block_str     (NSString *name);
NSData                               *cq_oc_block_bytes   (NSString *name);
NSArray<NSNumber *>                  *cq_oc_block_i64_list(NSString *name);
NSArray<NSString *>                  *cq_oc_block_str_list(NSString *name);
NSDictionary<NSString *, NSString *> *cq_oc_block_ss_map  (NSString *name);

void cq_oc_block_set_bool  (NSString *name, BOOL    value);
void cq_oc_block_set_int8  (NSString *name, int8_t  value);
void cq_oc_block_set_int16 (NSString *name, int16_t value);
void cq_oc_block_set_int32 (NSString *name, int32_t value);
void cq_oc_block_set_int64 (NSString *name, int64_t value);
void cq_oc_block_set_float (NSString *name, float   value);
void cq_oc_block_set_double(NSString *name, double  value);

void cq_oc_block_set_str     (NSString *name, NSString *value);
void cq_oc_block_set_bytes   (NSString *name, NSData   *value);
void cq_oc_block_set_i64_list(NSString *name, NSArray<NSNumber *> *value);
void cq_oc_block_set_str_list(NSString *name, NSArray<NSString *> *value);
void cq_oc_block_set_ss_map  (NSString *name, NSDictionary<NSString *, NSString *> *value);

//object reference:

//create a cq_obj that holds one reference count of $object.
//the return value need to release by cq_release_obj().
cq_obj *cq_retain_oc_obj(NSObject *object, NSString *cls);

//get the object that pointed by $obj.
//if $obj does not point a objc object or that object is not a $cls, return nil.
//it's equivalent to $cls is Nil and $cls is NSObject.class .
NSObject *cq_obj_raw_oc(cq_obj *obj, Class cls);
