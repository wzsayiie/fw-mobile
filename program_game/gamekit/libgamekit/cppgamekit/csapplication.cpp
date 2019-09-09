#include "csapplication.hh"
#include "cqopengl.h"
#include "cqwnd.h"

static cq_wnd *sWnd = NULL;

static void load(cq_wnd *wnd) {
}

static void gldraw(cq_wnd *wnd) {
    glClearColor(0.5, 0.6, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void csApplication::initializeIfNeeded() {
    if (sWnd != NULL) {
        return;
    }
    
    cq_wndproc proc = {nullptr};
    proc.load = load;
    proc.gldraw = gldraw;
    
    sWnd = cq_new_wnd();
    cq_set_wndproc(sWnd, &proc);
    cq_show_wnd(sWnd);
}
