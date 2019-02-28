package src.app.utility.application;

import android.app.Application;

import src.library.foundation.L;

public abstract class AppDelegate {

    //NOTE: these static member designed for thread safe.

    private static Application sApp;

    private static synchronized Application storedApp(Application app) {
        if (app != null) {
            sApp = app;
        }
        return sApp;
    }

    public static void initApp(Application app) {
        if (app != null) {
            L.i("init app context");
            storedApp(app);
        } else {
            L.e("try set null app context");
        }
    }

    public static Application getApp() {
        Application app = storedApp(null);
        if (app == null) {
            L.e("app context didn't set");
        }
        return app;
    }

    public void init() {
        L.i("init app delegate %s", L.string(this));
        onCreate();
    }

    protected abstract void onCreate();
}
