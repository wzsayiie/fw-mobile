package src.app.application;

import src.library.foundation.L;

public class CQCrashListener {

    private static CQCrashListener sInstance;

    public static CQCrashListener get() {
        if (sInstance == null) {
            L.i("init crash listener");
            sInstance = new CQCrashListener();
        }
        return sInstance;
    }

    public boolean lastLaunchCrashed() {
        return false;
    }
}
