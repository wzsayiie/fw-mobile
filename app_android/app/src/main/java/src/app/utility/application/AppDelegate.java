package src.app.utility.application;

import android.app.Application;

public abstract class AppDelegate {

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

    public static void initDelegate(AppDelegate delegate) {
        if (delegate != null) {
            L.i("init app delegate %s", L.string(delegate));
            delegate.onCreate();
        } else {
            L.e("try init null app delegate");
        }
    }

    protected abstract void onCreate();
}
