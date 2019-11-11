#pragma once

#include "csgamekit.hh"

struct ResPackage {
    
    static void load();
    
    static std::string packagePath();
    static std::string resourcesPath();
    static std::string scriptsPath();
};
