#pragma once

#include "cscomponent.hh"
#include "csgameobject.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

struct csObjectStorage {
    
    //create a game object or component:
    
    static csGameObjectRef createGameObject();
    static csComponentRef createComponet(cqClass *clazz);
    
    template<class T> static typename cqRef<T>::Strong createComponent() {
        csComponentRef component = createComponet(T::clazz());
        return cqObject::cast<T>(component);
    }
    
    //check a id is available or not:
    
    static csGKObjectRef check(int32_t id);
    
    template<class T> static bool available(int32_t id) {
        cqObjectRef object = check(id);
        return object && object->isKindOfClass(T::clazz());
    }
    
    template<class T> static typename cqRef<T>::Strong check(int32_t id) {
        cqObjectRef object = check(id);
        if (object != nullptr && object->isKindOfClass(T::clazz())) {
            return cqObject::cast<T>(object);
        }
        return nullptr;
    }
    
    //destroy a game object or component:
    
    static void destroy(int32_t id);
};

_CSGAMEKIT_END_VERSION_NS
