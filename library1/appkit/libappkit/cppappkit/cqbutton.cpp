#include "cqbutton.hh"

cq_member(cqButton) {
    cqLabelRef titleLabel;
    std::map<cqControlState, std::string> titles;
    std::map<cqControlState, cqColor> titleColors;
    bool touched = false;
};

void cqButton::init() {
    init(cqRect());
}

void cqButton::init(cqRect frame) {
    super::init(frame);
    
    dat->titleLabel = cqLabel::create(bounds());
    addSubview(dat->titleLabel);
}

cqLabelRef cqButton::titleLabel() {
    return dat->titleLabel;
}

void cqButton::setFrame(cqRect frame) {
    super::setFrame(frame);
    if (dat->titleLabel != nullptr) {
        dat->titleLabel->setFrame(bounds());
    }
}

static void displayTitleLabel(cqButton *self) {
    
    cqControlState state = self->state();
    
    //set title:
    std::string title;
    if (cqMap::contains(self->dat->titles, state)) {
        title = self->dat->titles[state];
    }
    self->dat->titleLabel->setText(title);
    
    //set title color:
    cqColor color;
    if (cqMap::contains(self->dat->titleColors, state)) {
        color = self->dat->titleColors[state];
    }
    if (color == cqColor::ClearColor) {
        //black is default.
        color = cqColor::BlackColor;
    }
    if (self->dat->touched) {
        //make color lighter.
      #define F(x) ((x) + 0.2F < 1.F ? (x) + 0.2F : 1.F)
        color.red   = F(color.red  );
        color.green = F(color.green);
        color.blue  = F(color.blue );
      #undef F
    }
    self->dat->titleLabel->setTextColor(color);
}

void cqButton::setTitleForState(cqControlState controlState, const std::string &title) {
    dat->titles[controlState] = title;
    if (controlState == state()) {
        displayTitleLabel(this);
    }
}

void cqButton::setTitleColorForState(cqControlState controlState, cqColor color) {
    dat->titleColors[controlState] = color;
    if (controlState == state()) {
        displayTitleLabel(this);
    }
}

void cqButton::touchesBegan(const std::set<cqTouchRef> &touches, cqEventRef event) {
    dat->touched = true;
    displayTitleLabel(this);
    sendEvent(cqControlEvent::TouchDown);
}

void cqButton::touchesMoved(const std::set<cqTouchRef> &touches, cqEventRef event) {
}

void cqButton::touchesEnded(const std::set<cqTouchRef> &touches, cqEventRef event) {
    dat->touched = false;
    displayTitleLabel(this);
    
    cqTouchRef one = *touches.begin();
    cqPoint point = one->locationInView(strongRef());
    if (bounds().contains(point)) {
        sendEvent(cqControlEvent::TouchUpInside);
    } else {
        sendEvent(cqControlEvent::TouchUpOutside);
    }
}
