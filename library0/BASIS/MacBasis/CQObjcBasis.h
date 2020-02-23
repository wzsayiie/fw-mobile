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

//interfaces for interaction with c:

struct cq_bytes   *cq_objc_mut_bytes  (NSMutableData                               *object);
struct cq_int64s  *cq_objc_mut_int64s (NSMutableArray<NSNumber *>                  *object);
struct cq_strings *cq_objc_mut_strings(NSMutableArray<NSString *>                  *object);
struct cq_ss_map  *cq_objc_mut_ss_map (NSMutableDictionary<NSString *, NSString *> *object);

struct cq_bytes   *cq_objc_bytes  (NSData                               *object);
struct cq_int64s  *cq_objc_int64s (NSArray<NSNumber *>                  *object);
struct cq_strings *cq_objc_strings(NSArray<NSString *>                  *object);
struct cq_ss_map  *cq_objc_ss_map (NSDictionary<NSString *, NSString *> *object);

void cq_objc_bytes_recv  (struct cq_bytes   *dst, const void *ptr, int32_t len);
void cq_objc_int64s_recv (struct cq_int64s  *dst, int64_t     val);
void cq_objc_strings_recv(struct cq_strings *dst, const char *val);
void cq_objc_ss_map_recv (struct cq_ss_map  *dst, const char *key, const char *val);

void cq_objc_bytes_send  (struct cq_bytes   *src, cq_bytes_recv   recv, struct cq_bytes   *dst);
void cq_objc_int64s_send (struct cq_int64s  *src, cq_int64s_recv  recv, struct cq_int64s  *dst);
void cq_objc_strings_send(struct cq_strings *src, cq_strings_recv recv, struct cq_strings *dst);
void cq_objc_ss_map_send (struct cq_ss_map  *src, cq_ss_map_recv  recv, struct cq_ss_map  *dst);

NSData                               *CQDataFrom   (cq_bytes_send   send, struct cq_bytes   *src);
NSArray<NSNumber *>                  *CQInt64sFrom (cq_int64s_send  send, struct cq_int64s  *src);
NSArray<NSString *>                  *CQStringsFrom(cq_strings_send send, struct cq_strings *src);
NSDictionary<NSString *, NSString *> *CQSSMapFrom  (cq_ss_map_send  send, struct cq_ss_map  *src);

void CQSendBytes  (NSData                               *src, cq_bytes_recv   recv, struct cq_bytes   *dst);
void CQSendInt64s (NSArray<NSNumber *>                  *src, cq_int64s_recv  recv, struct cq_int64s  *dst);
void CQSendStrings(NSArray<NSString *>                  *src, cq_strings_recv recv, struct cq_strings *dst);
void CQSendSSMap  (NSDictionary<NSString *, NSString *> *src, cq_ss_map_recv  recv, struct cq_ss_map  *dst);

struct cq_bytes   *CQStoreData   (NSData                               *object);
struct cq_int64s  *CQStoreInt64s (NSArray<NSNumber *>                  *object);
struct cq_strings *CQStoreStrings(NSArray<NSString *>                  *object);
struct cq_ss_map  *CQStoreSSMap  (NSDictionary<NSString *, NSString *> *object);
