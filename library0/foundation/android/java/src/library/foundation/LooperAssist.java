package src.library.foundation;

import android.os.Handler;
import android.os.Looper;

import src.library.basis.W;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class LooperAssist {

    public static void runOnMainLoop(Runnable task) {
        if (task != null) {
            Looper looper = Looper.getMainLooper();
            new Handler(looper).post(task);
        }
    }
}
