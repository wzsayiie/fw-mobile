package src.app.boot;

import src.library.foundation.L;

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
