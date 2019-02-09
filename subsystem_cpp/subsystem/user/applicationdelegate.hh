#pragma once

#include "cquikit.hh"

struct ApplicationDelegate : CQApplicationDelegate {
CQ_CLS(ApplicationDelegate , CQApplicationDelegate , _self_ApplicationDelegate);
    
    ApplicationDelegate();
    
    virtual void applicationDidFinishLaunching();
};
