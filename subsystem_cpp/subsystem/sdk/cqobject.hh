#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct CQObject {
    virtual ~CQObject() = default;
};

#define CQ_ITF(NAME)\
/**/    typedef shared_ptr<NAME> ref;\
/**/    template<typename... A> static NAME::ref create(A... a) {\
/**/        return make_shared<NAME>(a...);\
/**/    }

#define CQ_CLS(NAME, SUPER, DATA)\
/**/    private:\
/**/    typedef SUPER super;\
/**/    public:\
/**/    shared_ptr<struct DATA> self;\
/**/    CQ_ITF(NAME)

template<typename T> void C_INIT(shared_ptr<T> &value) {
    value = make_shared<T>();
}
