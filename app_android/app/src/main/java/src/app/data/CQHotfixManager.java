package src.app.data;

import src.library.foundation.L;

public class CQHotfixManager {

    private static class Singleton {
        static CQHotfixManager instance = new CQHotfixManager();
    }
    public static CQHotfixManager get() {
        return Singleton.instance;
    }

    private CQHotfixManager() {
        L.i("hotfix manager initialize");
    }
}
