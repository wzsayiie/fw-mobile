package src.app.utility.data;

import android.app.Activity;
import android.app.Application;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.os.Bundle;

import src.app.utility.application.AppDelegate;
import src.app.utility.application.L;
import src.app.utility.application.SingletonManager;

public class ActivityDispatcher implements Application.ActivityLifecycleCallbacks {

    public static ActivityDispatcher get() {
        return SingletonManager.get().getInstanceOf(ActivityDispatcher.class);
    }

    public ActivityDispatcher() {
        AppDelegate.getApp().registerActivityLifecycleCallbacks(this);
    }

    public void startActivity(String action, Bundle extras) {
        if (action == null || action.length() == 0) {
            L.e("try start a activity but specified action is empty");
            return;
        }
        if (mResumedActivity == null) {
            L.e("not found resumed activity as sender");
            return;
        }

        Intent intent = new Intent();
        intent.setAction(action);
        if (extras != null) {
            intent.putExtras(extras);
        }

        try {
            mResumedActivity.startActivity(intent);
        } catch (ActivityNotFoundException e) {
            L.e("activity not found: %s", e.toString());
        }
    }

    private Activity mResumedActivity;

    @Override
    public void onActivityCreated(Activity activity, Bundle savedInstanceState) {
        L.i("activity '%s' created", L.string(activity));
    }

    @Override
    public void onActivityStarted(Activity activity) {
        L.i("activity '%s' started", L.string(activity));
    }

    @Override
    public void onActivityResumed(Activity activity) {
        L.i("activity '%s' resumed", L.string(activity));

        mResumedActivity = activity;
        L.i("resumed activity is '%s'", L.string(mResumedActivity));
    }

    @Override
    public void onActivityPaused(Activity activity) {
        L.i("activity '%s' paused", L.string(activity));

        if (mResumedActivity == activity) {
            mResumedActivity = null;
            L.i("resumed activity reset null");
        }
    }

    @Override
    public void onActivityStopped(Activity activity) {
        L.i("activity '%s' stopped", L.string(activity));
    }

    @Override
    public void onActivitySaveInstanceState(Activity activity, Bundle outState) {
        L.i("activity '%s' saveState", L.string(activity));
    }

    @Override
    public void onActivityDestroyed(Activity activity) {
        L.i("activity '%s' Destroyed", L.string(activity));
    }
}
