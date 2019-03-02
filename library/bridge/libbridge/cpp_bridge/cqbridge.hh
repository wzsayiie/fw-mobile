#pragma once

#include "cqbridgecore.h"
#include <string>

template<class T> struct CQBridgeCPP;

template<> struct CQBridgeCPP<std::string> {
    static CQBridgeValue create(const std::string &value) {
        return CQBridgeCreateString(value.c_str(), (int32_t)value.size());
    }
};

template<> struct CQBridgeCPP<int32_t> {
    static CQBridgeValue create(int32_t value) {
        return CQBridgeCreateInt32(value);
    }
};
