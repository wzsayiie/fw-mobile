#include "cqctool.hh"
#include "cqfoundation.hh"
#include "cqlualibfoundation.h"
#include "cqlualibsubsystem.h"
#include "cqluasource.h"
#include "cqluavm.h"
#include "cqopengl.h"
#include "cqwnd.h"

static void load(cq_wnd *wnd) {
    
    //local files
    std::string caches_dir = cqPath::cachesDirectory();
    std::string lua_dir = cqPathString::append(caches_dir, "lua");
    if (!cqFileManager::get()->directoryExists(lua_dir)) {
        cqFileManager::get()->createDirectory(lua_dir, false);
    }
    I("lua work directory: %s", lua_dir.c_str());
    
    //open lua vm
    cq_lua_update_source(lua_dir.c_str());
    cq_lua_open_vm(lua_dir.c_str());
    
    //custom libraries
    cq_lua_load_lib_foundation();
    cq_lua_load_lib_subsystem();
    
    //run
    cq_lua_do_string("require 'cqruntime'");
}

static void gldraw(cq_wnd *wnd) {
    glClearColor(0.5, 0.6, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

extern "C" void _cq_lua_entry() {
    
    cq_wndproc proc = {nullptr};
    proc.load = load;
    proc.gldraw = gldraw;
    
    cq_wnd *wnd = cq_new_wnd();
    cq_set_wndproc(wnd, &proc);
    cq_show_wnd(wnd);
}
