#include "applicationdelegate.h"
#include "rootviewcontroller.h"

struct _self_ApplicationDelegate {
    CWindow::ref window;
};

ApplicationDelegate::ApplicationDelegate() {
    C_INIT(self);
}

void ApplicationDelegate::applicationDidFinishLaunching() {
    
    RootViewController::ref rootController = RootViewController::create();
    
    self->window = CWindow::create();
    self->window->setRootViewController(rootController);
    self->window->makeKeyAndVisible();
}

extern "C" void _main() {
    ApplicationDelegate::ref delegate = ApplicationDelegate::create();
    CApplicationMain(delegate);
}
