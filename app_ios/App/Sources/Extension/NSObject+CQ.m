#import "NSObject+CQ.h"

void CQStrongProperty(id object, const void *key, id value) {
    objc_setAssociatedObject(object, key, value, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

void CQCopyProperty(id object, const void *key, id value) {
    objc_setAssociatedObject(object, key, value, OBJC_ASSOCIATION_COPY_NONATOMIC);
}

id CQGetProperty(id object, const void *key) {
    return objc_getAssociatedObject(object, key);
}