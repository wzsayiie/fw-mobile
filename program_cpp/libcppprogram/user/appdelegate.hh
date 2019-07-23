#pragma once

#include "cquikit.hh"

cq_class(AppDelegate, cqApplicationDelegate) {
    
    void applicationDidFinishLaunching () override;
    void applicationWillEnterForeground() override;
    void applicationDidEnterBackground () override;
};
