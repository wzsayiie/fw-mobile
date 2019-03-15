#pragma once

#include "coruntime.hh"

struct iComponent {
    
    iComponent *call(coGUID method, iComponent *object0,
                     iComponent *object1 = 0,
                     iComponent *object2 = 0,
                     iComponent *object3 = 0);
    
    int64_t call(coGUID method, int64_t raw0,
                 int64_t raw1 = 0,
                 int64_t raw2 = 0,
                 int64_t raw3 = 0);
};

struct iComponentCalleeParams {
    int64_t a0;
    int64_t a1;
    int64_t a2;
    int64_t a3;
};

struct iComponentCallee {
    virtual void called(coGUID method, iComponentCalleeParams params, int64_t *ret);
    iComponent *_component;
};
