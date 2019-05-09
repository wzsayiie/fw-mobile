package src.app.data;

import android.os.Handler;
import android.os.Looper;

import src.app.application.CQAppDelegate;
import src.library.foundation.L;

public class CQBus {

    //NOTE: these static member designed for thread safe.

    public static void runOnMainThread(long delayMilliseconds, Runnable runnable) {
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
