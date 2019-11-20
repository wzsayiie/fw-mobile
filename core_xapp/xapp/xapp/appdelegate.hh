#pragma once

#include "cqappkit.hh"

cq_class(AppDelegate, cqResponder) {
};

cq_class(AppDelegateProxy, cqApplicationDelegate) {
    
    cq_as_proxy_of(AppDelegate)
    
    void applicationDidFinishLaunching () override;
    void applicationWillEnterForeground() override;
    void applicationDidEnterBackground () override;
};
