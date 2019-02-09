#pragma once

#include "cqbridgecore_p.h"
#include <string>

# ifdef ANDROID
#   include "cqandroidbridge.hh"
# endif

template<class T> struct CQValue;

template<> struct CQValue<std::string> {
    static CQType create(const std::string &value) {
        return CQCreateString(value.c_str(), (int32_t)value.size());
    }
};

template<class T> struct _CQValueInteger {
    static CQType create(T value) {
        return CQCreateInteger(value);
    }
};

template<> struct CQValue<int8_t > : _CQValueInteger<int8_t > {};
template<> struct CQValue<int16_t> : _CQValueInteger<int16_t> {};
template<> struct CQValue<int32_t> : _CQValueInteger<int32_t> {};
template<> struct CQValue<int64_t> : _CQValueInteger<int64_t> {};
