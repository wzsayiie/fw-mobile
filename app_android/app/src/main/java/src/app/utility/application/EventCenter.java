package src.app.utility.application;

import android.os.Handler;
import android.os.Looper;

public class EventCenter {

    public static void runOnMainThread(long delayMilliseconds, Runnable runnable) {
        if (delayMilliseconds < 0) {
            L.e("post delayed task but delay is '%ld'", delayMilliseconds);
            return;
        }
        if (runnable == null) {
            L.e("try posy a null task");
            return;
        }

        Looper looper = AppDelegate.getApp().getMainLooper();
        new Handler(looper).postDelayed(runnable, delayMilliseconds);
    }
}
