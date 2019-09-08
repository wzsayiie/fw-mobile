#pragma once

#include "cqgamekitbase.hh"

_CQGAMEKIT_BEGIN_VERSION_NS

struct cqLuaVM {
    static void open(const std::string &directory);
    static void close();
};

_CQGAMEKIT_END_VERSION_NS
