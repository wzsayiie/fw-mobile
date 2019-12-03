#include "cqcontrol.hh"

cq_member(cqControl) {
    cqControlState state = cqControlState::Normal;
    std::map<cqControlEvent, std::function<void ()>> actions;
};

cqControlState cqControl::state() {
    return dat->state;
}

void cqControl::setActionForEvent(cqControlEvent event, std::function<void ()> action) {
    if (cqMap::contains(dat->actions, event)) {
        
        if (action != nullptr) {
            dat->actions[event] = action;
        } else {
            dat->actions.erase(event);
        }
        
    } else {
        
        if (action != nullptr) {
            dat->actions[event] = action;
        }
    }
}

void cqControl::removeActionForEvent(cqControlEvent event) {
    dat->actions.erase(event);
}

void cqControl::sendEvent(cqControlEvent event) {
    if (cqMap::contains(dat->actions, event)) {
        auto &action = dat->actions[event];
        action();
    }
}
