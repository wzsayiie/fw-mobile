package src.app.mod;

import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;

import src.library.foundation.L;

public class TaskHelper {

    private static class Singleton {
        static TaskHelper instance = new TaskHelper();
    }
    public static TaskHelper get() {
        return Singleton.instance;
    }

    public void runOnMainThread(long delayMillis, Runnable task) {
        if (task == null) {
            L.e("try posy a null task to main thread");
            return;
        }

        Looper looper = Looper.getMainLooper();
        new Handler(looper).postDelayed(task, delayMillis);
    }

    public void runOnCurrentTread(long delayMillis, Runnable task) {
        if (task == null) {
            L.e("try posy a null task to current looper");
            return;
        }

        Looper looper = Looper.myLooper();
        new Handler(looper).postDelayed(task, delayMillis);
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

    public void runOnAnyThread(Runnable task) {
        if (task == null) {
            L.e("try post a null task to any work thread");
            return;
        }

        startThreadsIfNeeded();

        int index = (int)(Math.random() * WORK_THREAD_NUMBER);
        L.i("post task to work thread %d", index);

        Looper looper = mWorkThreads[index].getLooper();
        new Handler(looper).post(task);
    }
}
