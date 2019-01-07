package src.app.utility.application;

import android.app.Application;

public abstract class AppDelegate {

    private static Application sApp;

    public static void initApp(Application app) {
        if (app != null && sApp == null) {
            L.i("init app context");
            sApp = app;
        } else if (app == null) {
            L.e("try set null app context");
        } else /* sApp != null */ {
            L.e("try set app context repeatedly");
        }
    }

    public static Application getApp() {
        if (sApp == null) {
            L.e("app context didn't set");
        }
        return sApp;
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
