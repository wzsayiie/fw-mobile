package src.app.bootstrap;

import src.app.boot.AppDelegate;

public class ServiceAppDelegate extends AppDelegate {

    private static ServiceAppDelegate sInstance;

    static synchronized ServiceAppDelegate get() {
        if (sInstance == null) {
            sInstance = new ServiceAppDelegate();
        }
        return sInstance;
    }

    @Override
    protected void onCreate() {
    }
}
