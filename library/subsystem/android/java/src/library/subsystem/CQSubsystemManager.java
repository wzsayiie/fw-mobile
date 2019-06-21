package src.library.subsystem;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;

import src.library.foundation.CQUIContextFinder;
import src.library.foundation.L;

public class CQSubsystemManager {

    @SuppressLint("StaticFieldLeak")
    private static CQSubsystemManager sInstance;

    public static synchronized CQSubsystemManager get() {
        if (sInstance == null) {
            sInstance = new CQSubsystemManager();
        }
        return sInstance;
    }

    private Activity mSubsystemActivity;

    public void startSubsystem() {
        if (mSubsystemActivity != null) {
            L.i("subsystem was already running");
            return;
        }

        Activity rootActivity = CQUIContextFinder.get().findCurrentActivity();
        if (rootActivity == null) {
            L.e("not found current activity context");
            return;
        }

        Intent intent = new Intent(rootActivity, CQSubsystemActivity.class);
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
