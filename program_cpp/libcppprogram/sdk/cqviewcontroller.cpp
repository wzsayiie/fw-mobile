#include "cqviewcontroller.hh"

cq_member(cqViewController) {
    cqView::Ref view;
};

cqViewController::cqViewController() {
}

void cqViewController::viewDidLoad() {
}

void cqViewController::viewDidAppear() {
}

void cqViewController::viewDidDisappear() {
}

cqView::Ref cqViewController::view() {
    if (dat->view == nullptr) {
        loadView();
        if (dat->view != nullptr) {
            dat->view->setViewDelegate(strongRef());
        }
    }
    return dat->view;
}

void cqViewController::loadView() {
    dat->view = cqView::create();
}

cqResponder::Ref cqViewController::nextResponder() {
    //unimplemented
    return nullptr;
}
