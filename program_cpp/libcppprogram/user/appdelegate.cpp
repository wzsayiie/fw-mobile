#include "appdelegate.hh"
#include "rootviewcontroller.hh"
#include "cqhostapi.h"

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

//_cq_entry(entry) {
//    AppDelegateRef delegate = AppDelegate::create();
//    cqApplicationMain(delegate);
//}
