#include "gamelowroot.hh"
#include "cqfoundation.hh"
#include "cqlualibfoundation.h"
#include "cslualibgamekit.h"
#include "cqlualibsubsystem.h"
#include "respackage.hh"

cq_member(GameLowRoot) {
};

void GameLowRoot::awake() {
    ResPackage::load();
    
    //resources directory.
    std::string resourcesPath = ResPackage::resourcesPath();
    csResources::setResourcesDirectory(resourcesPath);
    
    //startup lua vm.
    std::string scriptsPath = ResPackage::scriptsPath();
    csLuaVM::open(scriptsPath);
    
    cq_lua_load_lib_foundation();
    cq_lua_load_lib_subsystem();
    cs_lua_load_lib_gamekit();

    cq_lua_do_string("require 'runtime'");
}

void GameLowRoot::start() {
}

void GameLowRoot::update() {
}
