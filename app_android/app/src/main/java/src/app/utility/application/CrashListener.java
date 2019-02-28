package src.app.utility.application;

import src.library.foundation.L;

public class CrashListener {

    private static CrashListener sInstance;

    public static CrashListener get() {
        if (sInstance == null) {
            L.i("init crash listener");
            sInstance = new CrashListener();
        }
        return sInstance;
    }

    public boolean lastLaunchCrashed() {
        return false;
    }
}
