#import <Foundation/Foundation.h>
#import <objc/runtime.h>
#import "cqcbasis.h"

//it's not supported to associate a weak object to the other object.
//OBJC_ASSOCIATION_ASSIGN holds wild pointer possibly.

void CQSetStrongProperty(id object, const void *key, id value);
void CQSetCopyProperty  (id object, const void *key, id value);

id CQGetProperty(id object, const void *key);

#define cq_synthesize_strong(GET, SET)\
/**/    - (id)GET {\
/**/        return CQGetProperty(self, @selector(GET));\
/**/    }\
/**/    - (void)SET:(id)value {\
/**/        CQSetStrongProperty(self, @selector(GET), value);\
/**/    }

#define cq_synthesize_copy(GET, SET)\
/**/    - (id)GET {\
/**/        return CQGetProperty(self, @selector(GET));\
/**/    }\
/**/    - (void)SET:(id)value {\
/**/        CQSetCopyProperty(self, @selector(GET), value);\
/**/    }

//NOTE: the inquiry of shared object is atomic.

#define cq_shared_object(CLASS)\
/**/    do {\
/**/        static id object = nil;\
/**/        static dispatch_once_t token;\
/**/        dispatch_once(&token, ^{\
/**/            object = [[CLASS alloc] init];\
/**/        });\
/**/        return object;\
/**/    } while (0)
