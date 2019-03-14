#include "istring.hh"

static const coGUID mthdSetUTF8    = coGUIDMake(s,e,t,u,t,f,8,_,_,_,_,_,_);
static const coGUID mthdUTF8Data   = coGUIDMake(u,t,f,8,d,a,t,a,_,_,_,_,_);
static const coGUID mthdUTF8Length = coGUIDMake(u,t,f,8,l,e,n,g,t,h,_,_,_);

void iString::setUTF8(int64_t data, int32_t length) {
    call(mthdSetUTF8, data, length);
}

int64_t iString::utf8Data() {
    return call(mthdUTF8Data, 0LL);
}

int32_t iString::utf8Length() {
    return (int32_t)call(mthdUTF8Length, 0LL);
}

void iString::setString(const std::string &string) {
    auto data = (int64_t)string.data();
    auto length = (int32_t)string.length();
    setUTF8(data, length);
}

std::string iString::string() {
    auto data = (const char *)utf8Data();
    return data != nullptr ? data : "";
}

iString *iStringCallee::component() {
    return (iString *)_component;
}

int64_t iStringCallee::called(coGUID method, iComponentCalleeParams params) {
    if (method == mthdSetUTF8) {
        auto data = params.a0;
        auto length = (int32_t)params.a1;
        component()->setUTF8(data, length);
        return 0;
    } else if (method == mthdUTF8Data) {
        return component()->utf8Data();
    } else if (method == mthdUTF8Length) {
        return component()->utf8Length();
    } else {
        return 0;
    }
}
