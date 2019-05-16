#include "appdelegate.hh"
#include "rootviewcontroller.hh"

cq_member(AppDelegate) {
    cqWindow::Ref window;
};

AppDelegate::AppDelegate() {
}

void AppDelegate::applicationDidFinishLaunching() {
    I("application launching");
    
    auto controller = RootViewController::create();
    
    dat->window = cqWindow::create();
    dat->window->setRootViewController(controller);
    dat->window->makeKeyAndVisible();
}

void _entry() {
    AppDelegate::Ref delegate = AppDelegate::create();
    cqApplicationMain(delegate);
}
