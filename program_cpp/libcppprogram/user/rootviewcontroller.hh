#pragma once

#include "cquikit.hh"

cq_class(RootViewController, cqViewController) {

    RootViewController();
    
    void viewDidLoad() override;
    void viewDidAppear() override;
    void viewDidDisappear() override;
    
    void touchesBegan(const std::set<cqTouch::Ref> &touches, cqEvent::Ref event) override;
    void touchesMoved(const std::set<cqTouch::Ref> &touches, cqEvent::Ref event) override;
    void touchesEnded(const std::set<cqTouch::Ref> &touches, cqEvent::Ref event) override;
};
