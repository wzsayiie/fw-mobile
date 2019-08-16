package src.app.mod;

import android.os.Handler;
import android.os.Looper;

import java.util.Timer;
import java.util.TimerTask;

import src.library.foundation.L;

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

        Timer timer = new Timer(true);

        TimerTask timerTask;
        if (tickOnCurrentLooper) {
            Looper looper = Looper.myLooper();
            timerTask = new TimerTask() {
                @Override
                public void run() {
                    new Handler(looper).post(() -> task.once(timer));
                }
            };
        } else {
            timerTask = new TimerTask() {
                @Override
                public void run() {
                    task.once(timer);
                }
            };
        }

        timer.schedule(timerTask, periodMillis, periodMillis);
        return timer;
    }
}
