#include "appdelegate.hh"
#include "rootviewcontroller.hh"

cq_member(AppDelegate) {
    cqWindow::ref window;
};

AppDelegate::AppDelegate() {
}

void AppDelegate::applicationDidFinishLaunching() {
    I("application launching");
    
    auto controller = RootViewController::create();
    
    self->window = cqWindow::create();
    self->window->setRootViewController(controller);
    self->window->makeKeyAndVisible();
}

void _entry() {
    AppDelegate::ref delegate = AppDelegate::create();
    cqApplicationMain(delegate);
}
