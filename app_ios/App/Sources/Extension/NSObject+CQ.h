#import <objc/runtime.h>

void CQStrongProperty(id object, const void *key, id value);
void CQCopyProperty  (id object, const void *key, id value);
id   CQGetProperty   (id object, const void *key);

#define _CQ_STER_S(T, G, S) - (void)S:T v {        CQStrongProperty(self, @selector(G), v); }
#define _CQ_STER_C(T, G, S) - (void)S:T v {        CQCopyProperty  (self, @selector(G), v); }
#define _CQ_GETTER(T, G)    - T     G     { return CQGetProperty   (self, @selector(G)   ); }

#define cq_synthesize_strong(T, G, S) _CQ_STER_S(T, G, S) _CQ_GETTER(T, G)
#define cq_synthesize_copy(  T, G, S) _CQ_STER_C(T, G, S) _CQ_GETTER(T, G)
