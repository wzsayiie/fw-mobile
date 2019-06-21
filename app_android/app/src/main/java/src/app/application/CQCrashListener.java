package src.app.application;

import src.library.foundation.L;

public class CQCrashListener {

    private static class Singleton {
        static CQCrashListener instance = new CQCrashListener();
    }
    public static CQCrashListener get() {
        return Singleton.instance;
    }

    private CQCrashListener() {
        L.i("crash listener initialize");
    }

    public boolean lastLaunchCrashed() {
        return false;
    }
}
