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

//data interfaces for interaction with c:

cq_bytes   *cq_bytes_cast_mut_oc  (NSMutableData *object);
cq_int64s  *cq_int64s_cast_mut_oc (NSMutableArray<NSNumber *> *object);
cq_strings *cq_strings_cast_mut_oc(NSMutableArray<NSString *> *object);
cq_ss_map  *cq_ss_map_cast_mut_oc (NSMutableDictionary<NSString *, NSString *> *object);

cq_bytes   *cq_bytes_cast_oc  (NSData *object);
cq_int64s  *cq_int64s_cast_oc (NSArray<NSNumber *> *object);
cq_strings *cq_strings_cast_oc(NSArray<NSString *> *object);
cq_ss_map  *cq_ss_map_cast_oc (NSDictionary<NSString *, NSString *> *object);

void cq_oc_bytes_receiver  (cq_bytes   *dst, const void *ptr, int32_t len);
void cq_oc_int64s_receiver (cq_int64s  *dst, int64_t     val);
void cq_oc_strings_receiver(cq_strings *dst, const char *val);
void cq_oc_ss_map_receiver (cq_ss_map  *dst, const char *key, const char *val);

void cq_oc_bytes_sender  (cq_bytes   *src, cq_bytes_receiver   recv, cq_bytes   *dst);
void cq_oc_int64s_sender (cq_int64s  *src, cq_int64s_receiver  recv, cq_int64s  *dst);
void cq_oc_strings_sender(cq_strings *src, cq_strings_receiver recv, cq_strings *dst);
void cq_oc_ss_map_sender (cq_ss_map  *src, cq_ss_map_receiver  recv, cq_ss_map  *dst);

NSData                               *cq_oc_bytes_from  (cq_bytes_sender   send, cq_bytes   *src);
NSArray<NSNumber *>                  *cq_oc_int64s_from (cq_int64s_sender  send, cq_int64s  *src);
NSArray<NSString *>                  *cq_oc_strings_from(cq_strings_sender send, cq_strings *src);
NSDictionary<NSString *, NSString *> *cq_oc_ss_map_from (cq_ss_map_sender  send, cq_ss_map  *src);

void cq_send_oc_bytes  (NSData                               *src, cq_bytes_receiver   recv, cq_bytes   *dst);
void cq_send_oc_int64s (NSArray<NSNumber *>                  *src, cq_int64s_receiver  recv, cq_int64s  *dst);
void cq_send_oc_strings(NSArray<NSString *>                  *src, cq_strings_receiver recv, cq_strings *dst);
void cq_send_oc_ss_map (NSDictionary<NSString *, NSString *> *src, cq_ss_map_receiver  recv, cq_ss_map  *dst);

cq_bytes   *cq_store_oc_bytes  (NSData *object);
cq_int64s  *cq_store_oc_int64s (NSArray<NSNumber *> *object);
cq_strings *cq_store_oc_strings(NSArray<NSString *> *object);
cq_ss_map  *cq_store_oc_ss_map (NSDictionary<NSString *, NSString *> *object);

//object reference:

//create a cq_obj that holds one reference count of $object.
//the return value need to release by cq_release_obj().
cq_obj *cq_retain_oc_obj(NSObject *object, NSString *cls);

//get the object that pointed by $obj.
//if $obj does not point a objc object or that object is not a $cls, return nil.
//it's equivalent to $cls is Nil and $cls is NSObject.class .
NSObject *cq_obj_raw_oc(cq_obj *obj, Class cls);
