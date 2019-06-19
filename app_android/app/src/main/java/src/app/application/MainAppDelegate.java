package src.app.application;

import src.app.data.CQActivityDispatcher;
import src.app.data.CQHotfixManager;
import src.library.foundation.L;

public class MainAppDelegate extends CQAppDelegate {

    private static MainAppDelegate sInstance;

    static synchronized MainAppDelegate get() {
        if (sInstance == null) {
            L.i("init app delegate");
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
