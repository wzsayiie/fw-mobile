package src.app.application;

import src.app.application.cq.AppDelegate;

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
