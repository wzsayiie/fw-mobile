#include "cqviewcontroller.hh"

struct _self_CQViewController {
    CQView::ref view;
};

CQViewController::CQViewController() {
}

void CQViewController::viewDidLoad() {
}

void CQViewController::viewDidAppear() {
}

void CQViewController::viewDidDisappear() {
}

CQView::ref CQViewController::view() {
    if (self->view == nullptr) {
        loadView();
    }
    return self->view;
}

void CQViewController::loadView() {
    self->view = CQView::create();
}
