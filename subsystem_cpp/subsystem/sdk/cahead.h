#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct CObject {
    virtual ~CObject() = default;
};

#define C_INTF(NAME)\
/**/    typedef shared_ptr<NAME> ref;\
/**/    template<typename... A> static NAME::ref create(A... a) {\
/**/        return make_shared<NAME>(a...);\
/**/    }

#define C_CLAS(NAME, SUPER, DATA)\
/**/    private:\
/**/    typedef SUPER super;\
/**/    public:\
/**/    shared_ptr<struct DATA> self;\
/**/    C_INTF(NAME)

template<typename T> void C_INIT(shared_ptr<T> &value) {
    value = make_shared<T>();
}
