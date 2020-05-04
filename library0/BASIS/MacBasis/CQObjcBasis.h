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

cq_bytes      *cq_oc_bytes     (NSData                               *object);
cq_int64_list *cq_oc_int64_list(NSArray<NSNumber *>                  *object);
cq_str_list   *cq_oc_str_list  (NSArray<NSString *>                  *object);
cq_ss_map     *cq_oc_ss_map    (NSDictionary<NSString *, NSString *> *object);

//oc block.
cq_block *cq_block_retain_oc(void (^block)(void));

//bridged oc object:
cq_object *cq_object_retain_oc(id object, NSString *cls);
id cq_object_oc(cq_object *object, Class cls);
