package src.app.application;

import src.app.utility.application.AppDelegate;
import src.app.utility.application.SingletonManager;

public class ServiceAppDelegate extends AppDelegate {

    static ServiceAppDelegate get() {
        return SingletonManager.get().getInstanceOf(ServiceAppDelegate.class);
    }

    @Override
    protected void onCreate() {
    }
}
