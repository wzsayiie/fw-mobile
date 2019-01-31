#pragma once

#include "bridge_core.h"
#include <string>

# ifdef ANDROID
#   include "bridge_android.h"
# endif

template<class T> struct BRGValue;

template<> struct BRGValue<std::string> {
    static BRGType create(const std::string &value) {
        return BRGCreateString(value.c_str(), (int32_t)value.size());
    }
};
