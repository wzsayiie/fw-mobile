package src.app.application;

import src.app.data.CQActivityDispatcher;
import src.app.data.CQHotfixManager;

public class MainAppDelegate extends CQAppDelegate {

    private static MainAppDelegate sInstance;

    static synchronized MainAppDelegate get() {
        if (sInstance == null) {
            sInstance = new MainAppDelegate();
        }
        return sInstance;
    }

    @Override
    public void onCreate() {
        CQActivityDispatcher.get();
        CQHotfixManager.get();
    }
}
