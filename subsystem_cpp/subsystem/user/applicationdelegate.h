#pragma once

#include "cuikit.h"

struct ApplicationDelegate : CApplicationDelegate {
C_CLAS(ApplicationDelegate , CApplicationDelegate , _self_ApplicationDelegate);
    
    ApplicationDelegate();
    
    virtual void applicationDidFinishLaunching();
};
