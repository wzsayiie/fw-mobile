#include "csobjectstorage.hh"
#include "csanimation.hh"
#include "csanimator.hh"
#include "cscamera.hh"
#include "cscodebehaviour.hh"
#include "cscollider.hh"
#include "csmapfilter.hh"
#include "csmaprenderder.hh"
#include "csrigidbody.hh"
#include "cstransform.hh"

//create a game object or component:

csGameObjectRef csObjectStorage::createGameObject() {
    return nullptr;
}

csComponentRef csObjectStorage::createComponet(cqClass *clazz) {
    return nullptr;
}

//check a id is available or not:

csGKObjectRef csObjectStorage::check(int32_t id) {
    return nullptr;
}

//destroy a game object or component:

void csObjectStorage::destroy(int32_t id) {
}
