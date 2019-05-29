#include "appdelegate.hh"
#include "rootviewcontroller.hh"

cq_member(AppDelegate) {
    cqWindowRef window;
};

AppDelegate::AppDelegate() {
}

void AppDelegate::applicationDidFinishLaunching() {
    auto controller = RootViewController::create();
    
    dat->window = cqWindow::create();
    dat->window->setRootViewController(controller);
    dat->window->makeKeyAndVisible();
}

void _cq_sdk_entry() {
    AppDelegateRef delegate = AppDelegate::create();
    cqApplicationMain(delegate);
}
