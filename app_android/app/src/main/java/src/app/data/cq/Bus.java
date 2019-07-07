package src.app.data.cq;

import android.os.Handler;
import android.os.Looper;

import src.app.application.cq.AppDelegate;
import src.library.foundation.L;

public class Bus {

    private static class Singleton {
        static Bus instance = new Bus();
    }
    public static Bus get() {
        return Singleton.instance;
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

        Looper looper = AppDelegate.getApp().getMainLooper();
        new Handler(looper).postDelayed(runnable, delayMilliseconds);
    }
}
