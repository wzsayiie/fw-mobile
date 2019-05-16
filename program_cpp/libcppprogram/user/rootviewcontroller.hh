#pragma once

#include "cquikit.hh"

cq_class(RootViewController, cqViewController) {

    RootViewController();
    
    void viewDidLoad() override;
    void viewDidAppear() override;
    void viewDidDisappear() override;
};
