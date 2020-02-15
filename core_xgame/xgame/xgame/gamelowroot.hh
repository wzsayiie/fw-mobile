#pragma once

#include "csgamekit.hh"

cq_class(GameLowRoot, csScript) {
    
    void onAwake () override;
    void onStart () override;
    void onUpdate() override;
};
