package src.app.mod;

import src.library.basis.W;
import src.library.foundation.L;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
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
