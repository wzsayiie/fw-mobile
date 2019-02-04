#include "cviewcontroller.h"

struct _self_CViewController {
    CView::ref view;
};

CViewController::CViewController() {
    C_INIT(self);
}

void CViewController::viewDidLoad() {
}

void CViewController::viewDidAppear() {
}

void CViewController::viewDidDisappear() {
}

CView::ref CViewController::view() {
    if (self->view == nullptr) {
        loadView();
    }
    return self->view;
}

void CViewController::loadView() {
    self->view = CView::create();
}
