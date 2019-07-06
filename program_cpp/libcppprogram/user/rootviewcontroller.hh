#pragma once

#include "cquikit.hh"

cq_class(RootViewController, cqViewController) {
    
    void viewDidLoad() override;
    
    void touchesBegan(const std::set<cqTouchRef> &touches, cqEventRef event) override;
    void touchesMoved(const std::set<cqTouchRef> &touches, cqEventRef event) override;
    void touchesEnded(const std::set<cqTouchRef> &touches, cqEventRef event) override;
};
