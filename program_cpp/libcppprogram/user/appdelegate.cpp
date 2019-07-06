#include "appdelegate.hh"
#include "rootviewcontroller.hh"
#include "cqwindow.h"

cq_member(AppDelegate) {
    cqWindowRef window;
};

void AppDelegate::applicationDidFinishLaunching() {
    auto controller = RootViewController::create();
    
    dat->window = cqWindow::create();
    dat->window->setRootViewController(controller);
    dat->window->makeKeyAndVisible();
}

extern "C" void _cq_cpp_entry() {
    AppDelegateRef delegate = AppDelegate::create();
    cqApplication::main(delegate);
}
