package src.app.utility.data;

import android.os.Handler;
import android.os.Looper;

import src.app.utility.application.AppDelegate;
import src.app.utility.application.L;

public class Bus {

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
