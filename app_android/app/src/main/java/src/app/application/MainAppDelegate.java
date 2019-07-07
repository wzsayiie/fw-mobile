package src.app.application;

import src.app.application.cq.AppDelegate;
import src.app.data.cq.ActivityDispatcher;
import src.app.data.cq.HotfixManager;

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
