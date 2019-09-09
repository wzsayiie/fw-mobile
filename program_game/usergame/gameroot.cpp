#include "gameroot.hh"
#include "cqctool.hh"
#include "cqfoundation.hh"
#include "cqlualibfoundation.h"
#include "cqlualibsubsystem.h"
#include "csluavm.hh"
#include "luasource.hh"

cq_member(GameRoot) {
};

static void startupLuaVM() {
    //local files
    std::string cachesDirectory = cqPath::cachesDirectory();
    std::string luaDirectory = cqPathString::append(cachesDirectory, "lua");
    if (!cqFileManager::get()->directoryExists(luaDirectory)) {
        cqFileManager::get()->createDirectory(luaDirectory, false);
    }
    I("lua work directory: %s", luaDirectory.c_str());
    
    //open lua vm
    LuaSource::update(luaDirectory);
    csLuaVM::open(luaDirectory);
    
    //custom libraries
    cq_lua_load_lib_foundation();
    cq_lua_load_lib_subsystem();
    
    //run
    cq_lua_do_string("require 'cqruntime'");
}

void GameRoot::awake() {
    startupLuaVM();
}
