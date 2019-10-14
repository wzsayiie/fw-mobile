package src.app.mod;

import android.os.Handler;
import android.os.Looper;

import java.util.Timer;
import java.util.TimerTask;

import src.library.basis.W;
import src.library.foundation.L;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
public class TimerAssist {

    public interface Task {
        void once(Timer timer);
    }

    public static Timer schedule(boolean tickOnCurrentLooper, long periodMillis, Task task) {
        if (periodMillis <= 0) {
            L.e("try start a timer but period is smaller than 0");
            return null;
        }
        if (task == null) {
            L.e("try start a timer but task is null");
            return null;
        }

        if (tickOnCurrentLooper) {

            Looper looper = Looper.myLooper();
            if (looper == null) {
                L.e("failed to get current looper");
                return null;
            }

            Timer timer = new Timer(true);
            TimerTask timerTask = new TimerTask() {
                @Override
                public void run() {
                    new Handler(looper).post(() -> task.once(timer));
                }
            };

            timer.schedule(timerTask, periodMillis, periodMillis);
            return timer;

        } else {

            Timer timer = new Timer(true);
            TimerTask timerTask = new TimerTask() {
                @Override
                public void run() {
                    task.once(timer);
                }
            };

            timer.schedule(timerTask, periodMillis, periodMillis);
            return timer;
        }
    }
}
