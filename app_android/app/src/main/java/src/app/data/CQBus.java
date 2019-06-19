package src.app.data;

import android.os.Handler;
import android.os.Looper;

import src.app.application.CQAppDelegate;
import src.library.foundation.L;

public class CQBus {

    private static CQBus sInstance;

    public static synchronized CQBus get() {
        if (sInstance == null) {
            sInstance = new CQBus();
        }
        return sInstance;
    }

    public void runOnMainThread(long delayMilliseconds, Runnable runnable) {
        if (delayMilliseconds < 0) {
            L.e("post delayed task but delay is '%ld'", delayMilliseconds);
            return;
        }
        if (runnable == null) {
            L.e("try posy a null task");
            return;
        }

        Looper looper = CQAppDelegate.getApp().getMainLooper();
        new Handler(looper).postDelayed(runnable, delayMilliseconds);
    }
}
