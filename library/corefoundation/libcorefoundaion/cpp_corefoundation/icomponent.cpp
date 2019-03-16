#include "icomponent.hh"

iComponent *iComponent::call
/**/(coGUID method, iComponent *obj0, iComponent *obj1, iComponent *obj2, iComponent *obj3) {
    return nullptr;
}

int64_t iComponent::call
/**/(coGUID method, int64_t raw0, int64_t raw1, int64_t raw2, int64_t raw3) {
    return 0;
}

void iComponentCallee::called(coGUID method, iComponentCalleeParams params, int64_t *ret) {
}
