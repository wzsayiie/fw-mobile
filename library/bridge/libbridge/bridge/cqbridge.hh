#pragma once

#include "cqbridgecore.h"
#include <string>

# ifdef ANDROID
#   include "cqandroidbridge.hh"
# endif

template<class T> struct CQValueMaker;

template<> struct CQValueMaker<std::string> {
    static CQValue create(const std::string &value) {
        return CQCreateString(value.c_str(), (int32_t)value.size());
    }
};

template<> struct CQValueMaker<int32_t> {
    static CQValue create(int32_t value) {
        return CQCreateInt32(value);
    }
};
