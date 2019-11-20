#include "appdelegate.hh"
#include "cqctool.hh"
#include "cqfoundation.hh"
#include "rootviewcontroller.hh"

cq_member(AppDelegate) {
    cqWindowRef window;
};

cq_member(AppDelegateProxy) {
};

void AppDelegateProxy::applicationDidFinishLaunching() {
    if (auto object = castCore()) {
        
        auto controller = RootViewController::create();
    
        object->dat->window = cqWindow::create();
        object->dat->window->setRootViewController(controller);
        object->dat->window->makeKeyAndVisible();
    }
}

void AppDelegateProxy::applicationWillEnterForeground() {
}

void AppDelegateProxy::applicationDidEnterBackground() {
}

extern "C" void _cq_app_entry() {
    //NOTE: hold a strong reference of AppDelegate.
    static AppDelegateRef delegate = AppDelegate::create();
    
    AppDelegateProxyRef proxy = AppDelegateProxy::create(delegate);
    cqApplication::main(proxy);
}
