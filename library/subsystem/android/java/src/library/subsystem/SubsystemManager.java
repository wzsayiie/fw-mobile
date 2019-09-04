package src.library.subsystem;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;

import src.library.basis.W;
import src.library.foundation.L;
import src.library.foundation.UIContextAssist;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class SubsystemManager {

    private static class Singleton {
        @SuppressLint("StaticFieldLeak")
        static SubsystemManager instance = new SubsystemManager();
    }
    public static SubsystemManager get() {
        return Singleton.instance;
    }

    private Activity mSubsystemActivity;

    public void startSubsystem() {
        if (mSubsystemActivity != null) {
            L.i("subsystem was already running");
            return;
        }

        Activity rootActivity = UIContextAssist.currentActivity();
        if (rootActivity == null) {
            L.e("not found current activity context");
            return;
        }

        Intent intent = new Intent(rootActivity, SubsystemActivity.class);
        rootActivity.startActivity(intent);
    }

    //the manager need record subsystem activity's instance,
    //otherwise stopSubsystem() can't work.
    void setSubsystemActivityInstance(Activity activity) {
        mSubsystemActivity = activity;
    }

    public void stopSubsystem() {
        if (mSubsystemActivity == null) {
            L.i("there was no any subsystem");
            return;
        }

        mSubsystemActivity.finish();
        mSubsystemActivity = null;
    }
}
