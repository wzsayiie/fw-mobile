#pragma once

#include "csgamekitbase.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

struct csLuaVM {
    static void open(const std::string &directory);
    static void close();
};

_CSGAMEKIT_END_VERSION_NS
