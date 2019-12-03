#pragma once

#include "cqcontrol.hh"
#include "cqlabel.hh"

_CQAPPKIT_BEGIN_VERSION_NS

cq_class(cqButton, cqControl) {
    
    void init();
    void init(cqRect frame);
    
    virtual cqLabelRef titleLabel();
    
    void setFrame(cqRect frame) override;
    
    virtual void setTitleForState(cqControlState state, const std::string &title);
    virtual void setTitleColorForState(cqControlState state, cqColor color);
    
    void touchesBegan(const std::set<cqTouchRef> &touches, cqEventRef event) override;
    void touchesMoved(const std::set<cqTouchRef> &touches, cqEventRef event) override;
    void touchesEnded(const std::set<cqTouchRef> &touches, cqEventRef event) override;
};

_CQAPPKIT_END_VERSION_NS
