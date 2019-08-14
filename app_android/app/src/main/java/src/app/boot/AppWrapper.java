package src.app.boot;

import android.app.Application;

import src.library.foundation.L;

public abstract class AppWrapper {

    private static Application sApp;

    private static synchronized Application storedApp(char intent, Application app) {
        switch (intent) {
            case '+': return sApp = app;
            case '?': return sApp;
            default : return null;
        }
    }

    public static void assignApp(Application app) {
        if (app != null) {
            L.i("init app context");
            storedApp('+', app);
        } else {
            L.e("try set null app context");
        }
    }

    public static Application getApp() {
        Application app = storedApp('?', null);
        if (app == null) {
            L.e("app context didn't assign");
        }
        return app;
    }
}
