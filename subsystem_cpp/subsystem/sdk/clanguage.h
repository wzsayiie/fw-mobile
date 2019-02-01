#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

struct CInterface {
    virtual ~CInterface() {}
};

#define c_interface(NAME, BASE)\
/**/    struct NAME;\
/**/    typedef shared_ptr<NAME> NAME##Ref;\
/**/    struct NAME : BASE

struct CObject {
    virtual ~CObject() {}
};
