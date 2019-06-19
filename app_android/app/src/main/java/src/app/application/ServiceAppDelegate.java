package src.app.application;

import src.library.foundation.L;

public class ServiceAppDelegate extends CQAppDelegate {

    private static ServiceAppDelegate sInstance;

    static synchronized ServiceAppDelegate get() {
        if (sInstance == null) {
            L.i("init service delegate");
            sInstance = new ServiceAppDelegate();
        }
        return sInstance;
    }

    @Override
    protected void onCreate() {
    }
}
