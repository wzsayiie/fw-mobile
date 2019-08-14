package src.app.data.cq;

import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;

import src.app.application.cq.AppDelegate;
import src.library.foundation.L;

public class TaskDispatcher {

    private static class Singleton {
        static TaskDispatcher instance = new TaskDispatcher();
    }
    public static TaskDispatcher get() {
        return Singleton.instance;
    }

    public void runOnMainThread(Runnable task) {
        if (task == null) {
            L.e("try posy a null task to main thread");
            return;
        }

        Looper looper = AppDelegate.getApp().getMainLooper();
        new Handler(looper).post(task);
    }

    private final int WORK_THREAD_NUMBER = 4;
    private HandlerThread[] mWorkThreads;

    private synchronized void startThreadsIfNeeded() {
        if (mWorkThreads != null) {
            return;
        }

        L.i("task dispatch start work threads");
        mWorkThreads = new HandlerThread[WORK_THREAD_NUMBER];
        for (int it = 0; it < WORK_THREAD_NUMBER; ++it) {
            mWorkThreads[it] = new HandlerThread("TaskThread" + it);
            mWorkThreads[it].start();
        }
    }

    public void run(Runnable task) {
        if (task == null) {
            L.e("try post a null task to work thread");
            return;
        }

        startThreadsIfNeeded();

        int index = (int)(Math.random() * WORK_THREAD_NUMBER);
        L.i("post task to work thread %d", index);

        Looper looper = mWorkThreads[index].getLooper();
        new Handler(looper).post(task);
    }
}
