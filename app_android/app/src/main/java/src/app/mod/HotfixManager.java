package src.app.mod;

import src.library.foundation.L;

public class HotfixManager {

    private static class Singleton {
        static HotfixManager instance = new HotfixManager();
    }
    public static HotfixManager get() {
        return Singleton.instance;
    }

    private HotfixManager() {
        L.i("hotfix manager initialize");
    }
}
