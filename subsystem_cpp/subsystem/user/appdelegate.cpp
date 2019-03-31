#include "appdelegate.hh"
#include "rootviewcontroller.hh"

struct _self_AppDelegate {
    cqWindow::ref window;
};

AppDelegate::AppDelegate() {
}

void AppDelegate::applicationDidFinishLaunching() {
    I("application launching");
    
    RootViewController::ref controller = RootViewController::create();
    
    self->window = cqWindow::create();
    self->window->setRootViewController(controller);
    self->window->makeKeyAndVisible();
}

extern "C" void _main() {
    AppDelegate::ref delegate = AppDelegate::create();
    cqApplicationMain(delegate);
}
