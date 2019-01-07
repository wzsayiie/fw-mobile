package src.app.application;

import src.app.utility.application.AppDelegate;
import src.app.utility.application.SingletonManager;
import src.app.utility.data.ActivityDispatcher;

public class MainAppDelegate extends AppDelegate {

    static MainAppDelegate get() {
        return SingletonManager.get().getInstanceOf(MainAppDelegate.class);
    }

    @Override
    public void onCreate() {
        ActivityDispatcher.get();
    }
}
