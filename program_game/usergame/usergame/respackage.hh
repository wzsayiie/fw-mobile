#pragma once

#include "csgamekit.hh"

struct ResPackage {
    static void load();
    
    static void startupLuaVM();
    static std::string pathForFile(const std::string &name);
};
