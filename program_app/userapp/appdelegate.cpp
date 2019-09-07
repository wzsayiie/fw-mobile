#include "appdelegate.hh"
#include "cqctool.hh"
#include "cqfoundation.hh"
#include "rootviewcontroller.hh"

cq_member(AppDelegate) {
    cqWindowRef window;
};

void AppDelegate::applicationDidFinishLaunching() {
    auto controller = RootViewController::create();
    
    dat->window = cqWindow::create();
    dat->window->setRootViewController(controller);
    dat->window->makeKeyAndVisible();
}

void AppDelegate::applicationWillEnterForeground() {
}

void AppDelegate::applicationDidEnterBackground() {
}

extern "C" void _cq_app_entry() {
    AppDelegateRef delegate = AppDelegate::create();
    cqApplication::main(delegate);
}
