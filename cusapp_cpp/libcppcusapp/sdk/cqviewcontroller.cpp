#include "cqviewcontroller.hh"

cq_member(cqViewController) {
    cqView::ref view;
};

cqViewController::cqViewController() {
}

void cqViewController::viewDidLoad() {
}

void cqViewController::viewDidAppear() {
}

void cqViewController::viewDidDisappear() {
}

cqView::ref cqViewController::view() {
    if (self->view == nullptr) {
        loadView();
    }
    return self->view;
}

void cqViewController::loadView() {
    self->view = cqView::create();
}
