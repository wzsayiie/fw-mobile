#include "luacontrol.hh"
#include "cqctool.hh"
#include "cqfoundation.hh"
#include "cqlualibfoundation.h"
#include "cqlualibsubsystem.h"
#include "csluavm.hh"
#include "luasource.hh"

void LuaControl::startup() {
    //local files:
    std::string cachesDir = cqPath::cachesDirectory();
    std::string luaDir = cqPathString::append(cachesDir, "lua");
    if (!cqFileManager::get()->directoryExists(luaDir)) {
        cqFileManager::get()->createDirectory(luaDir, false);
    }
    I("lua work directory: %s", luaDir.c_str());
    
    //open lua vm:
    LuaSource::update(luaDir);
    csLuaVM::open(luaDir);
    
    //custom libraries:
    cq_lua_load_lib_foundation();
    cq_lua_load_lib_subsystem();
    
    //run:
    cq_lua_do_string("require 'runtime'");
}
