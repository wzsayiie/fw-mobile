package src.app.boot;

import src.library.basis.W;
import src.library.foundation.L;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
public class CrashListener {

    private static class Singleton {
        static CrashListener instance = new CrashListener();
    }
    public static CrashListener get() {
        return Singleton.instance;
    }

    private CrashListener() {
        L.i("crash listener initialize");
    }

    public boolean lastLaunchCrashed() {
        return false;
    }
}
