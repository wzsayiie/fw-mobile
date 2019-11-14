#include "respackage.hh"
#include "cqfoundation.hh"
#include "cqctool.hh"

std::string loadOnAndroid() {
    std::string cachesDir = cqPath::cachesDirectory();
    std::string path = cqPathString::append(cachesDir, "RES");
    
    cqAndroidBundleRef bundle = cqAndroidBundle::get();
    bundle->copyAsset("xgameres.bundle", path);
    
    return path;
}

std::string loadOnIOS() {
    std::string bundlePath = cqIOSBundle::get()->bundlePath();
    std::string path = cqPathString::append(bundlePath, "xgameres.bundle");
    return path;
}

static std::string sPackagePath;

void ResPackage::load() {
#if CQ_ON_ANDROID
    sPackagePath = loadOnAndroid();
#elif CQ_ON_IOS
    sPackagePath = loadOnIOS();
#else
    #error "unknown platform"
#endif
}

std::string ResPackage::packagePath() {
    return sPackagePath;
}

std::string ResPackage::resourcesPath() {
    return cqPathString::append(sPackagePath, "resources");
}

std::string ResPackage::scriptsPath() {
    return cqPathString::append(sPackagePath, "scripts");
}
