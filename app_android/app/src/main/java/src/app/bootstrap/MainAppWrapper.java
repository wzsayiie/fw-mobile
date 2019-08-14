package src.app.bootstrap;

import src.app.boot.AppWrapper;
import src.app.com.ActivityDispatcher;
import src.app.mod.HotfixManager;
import src.library.foundation.L;

public class MainAppWrapper extends AppWrapper {

    private static class Singleton {
        static MainAppWrapper instance = new MainAppWrapper();
    }
    public static MainAppWrapper get() {
        return Singleton.instance;
    }

    private MainAppWrapper() {
        L.i("main app initialize");

        ActivityDispatcher.get();
        HotfixManager.get();
    }
}
