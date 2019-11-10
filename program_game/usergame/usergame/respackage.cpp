#include "respackage.hh"
#include "cqctool.hh"
#include "cqfoundation.hh"
#include "cqlualibfoundation.h"
#include "cslualibgamekit.h"
#include "cqlualibsubsystem.h"
#include "csluavm.hh"

static std::string sPackagePath;
static std::string sResourcesPath;
static std::string sScriptsPath;

std::string loadOnAndroid() {
    std::string cachesDir = cqPath::cachesDirectory();
    std::string path = cqPathString::append(cachesDir, "RES");
    
    cqAndroidBundleRef bundle = cqAndroidBundle::get();
    bundle->copyAsset("usergameres.bundle", path);
    
    return path;
}

std::string loadOnIOS() {
    std::string bundlePath = cqIOSBundle::get()->bundlePath();
    std::string path = cqPathString::append(bundlePath, "usergameres.bundle");
    return path;
}

void ResPackage::load() {
#if CQ_ON_ANDROID
    sPackagePath = loadOnAndroid();
#elif CQ_ON_IOS
    sPackagePath = loadOnIOS();
#else
    #error "unknown platform"
#endif
    
    sResourcesPath = cqPathString::append(sPackagePath, "resources");
    sScriptsPath = cqPathString::append(sPackagePath, "scripts");
}

void ResPackage::startupLuaVM() {
    if (sScriptsPath.empty()) {
        return;
    }
    
    //open lua vm:
    csLuaVM::open(sScriptsPath);

    //custom libraries:
    cq_lua_load_lib_foundation();
    cq_lua_load_lib_subsystem();
    cs_lua_load_lib_gamekit();

    //run:
    cq_lua_do_string("require 'runtime'");
}

std::string ResPackage::pathForFile(const std::string &name) {
    if (sResourcesPath.empty()) {
        return "";
    }
    
    std::string path = cqPathString::append(sResourcesPath, name);
    if (cqFileManager::get()->fileExists(path)) {
        return path;
    } else {
        return "";
    }
}
