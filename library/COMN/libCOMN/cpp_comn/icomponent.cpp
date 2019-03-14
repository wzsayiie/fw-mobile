#include "icomponent.hh"

iComponent *iComponent::call(coGUID method, iComponent *object0, iComponent *object1, iComponent *object2, iComponent *object3) {
    return nullptr;
}

int64_t iComponent::call(coGUID  method, int64_t raw0, int64_t raw1, int64_t raw2, int64_t raw3) {
    return 0;
}

int64_t iComponentCallee::called(coGUID method, iComponentCalleeParams params) {
    return 0;
}
