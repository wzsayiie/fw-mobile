#pragma once

#include "csgamekitbase.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csGKObject, cqObject) {
    
    static void dontDestroyOnLoad(csGKObjectRef object);
    static void destroy(csGKObjectRef object);
    
    //if ptr is a valid pointer to instance of csGKObject,
    //return the strong reference of the object.
    static csGKObjectRef _checkout(void *ptr);
    
    template<class T> static typename cqRef<T>::Strong checkout(void *ptr) {
        return cqObject::cast<T>(_checkout(ptr));
    }
    template<class T> static typename cqRef<T>::Strong checkout(int64_t index) {
        return cqObject::cast<T>(_checkout(*(void **)&index));
    }
    
    csGKObject ();
    ~csGKObject();
};

_CSGAMEKIT_END_VERSION_NS
