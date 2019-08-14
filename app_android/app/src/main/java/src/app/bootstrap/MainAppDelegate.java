package src.app.bootstrap;

import src.app.boot.AppDelegate;
import src.app.mod.ActivityDispatcher;
import src.app.mod.HotfixManager;

public class MainAppDelegate extends AppDelegate {

    private static MainAppDelegate sInstance;

    static synchronized MainAppDelegate get() {
        if (sInstance == null) {
            sInstance = new MainAppDelegate();
        }
        return sInstance;
    }

    @Override
    public void onCreate() {
        ActivityDispatcher.get();
        HotfixManager.get();
    }
}
