#include "appdelegate.hh"
#include "rootviewcontroller.hh"

cq_member(AppDelegate) {
    cqWindow::ref window;
};

AppDelegate::AppDelegate() {
}

void AppDelegate::applicationDidFinishLaunching(cqWindow::ref window) {
    I("application launching");
    
    RootViewController::ref controller = RootViewController::create();
    window->setRootViewController(controller);
}

void _entry() {
    AppDelegate::ref delegate = AppDelegate::create();
    cqApplicationMain(delegate);
}
