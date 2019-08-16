package src.app.mod;

import src.library.foundation.L;

public class HotfixHelper {

    private static class Singleton {
        static HotfixHelper instance = new HotfixHelper();
    }
    public static HotfixHelper get() {
        return Singleton.instance;
    }

    private HotfixHelper() {
        L.i("hotfix manager initialize");
    }
}
