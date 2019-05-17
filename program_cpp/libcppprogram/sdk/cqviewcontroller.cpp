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

cqResponder::Ref cqViewController::nextResponder() {
    return view()->superview();
}
