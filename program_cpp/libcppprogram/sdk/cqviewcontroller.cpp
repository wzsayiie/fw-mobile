#include "cqviewcontroller.hh"

cq_member(cqViewController) {
    cqViewRef view;
};

cqViewController::cqViewController() {
}

void cqViewController::viewDidLoad() {
}

void cqViewController::viewDidAppear() {
}

void cqViewController::viewDidDisappear() {
}

cqViewRef cqViewController::view() {
    if (dat->view == nullptr) {
        loadView();
    }
    return dat->view;
}

void cqViewController::loadView() {
    dat->view = cqView::create();
    if (dat->view != nullptr) {
        dat->view->setViewController(strongRef());
        viewDidLoad();
    }
}

cqResponderRef cqViewController::nextResponder() {
    return view()->superview();
}
