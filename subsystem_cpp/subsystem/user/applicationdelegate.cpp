#include "applicationdelegate.hh"
#include "rootviewcontroller.hh"

struct _self_ApplicationDelegate {
    CQWindow::ref window;
};

ApplicationDelegate::ApplicationDelegate() {
    C_INIT(self);
}

void ApplicationDelegate::applicationDidFinishLaunching() {
    
    RootViewController::ref rootController = RootViewController::create();
    
    self->window = CQWindow::create();
    self->window->setRootViewController(rootController);
    self->window->makeKeyAndVisible();
}

extern "C" void _main() {
    ApplicationDelegate::ref delegate = ApplicationDelegate::create();
    CQApplicationMain(delegate);
}
