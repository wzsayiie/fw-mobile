package src.app.utility.data;

import android.app.Activity;
import android.app.Application;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.os.Bundle;

import src.app.utility.application.AppDelegate;
import src.app.utility.application.L;
import src.app.utility.application.SingletonManager;

public class ActivityDispatcher {

    public static ActivityDispatcher get() {
        return SingletonManager.get().getInstanceOf(ActivityDispatcher.class);
    }

    //activity lifecycle

    public ActivityDispatcher() {

        AppDelegate.getApp().registerActivityLifecycleCallbacks(new Application.ActivityLifecycleCallbacks() {

            public void onActivitySaveInstanceState(Activity a, Bundle b) { onActSaveInstanceState(a, b); }
            public void onActivityCreated          (Activity a, Bundle b) { onActCreated(a, b);}

            public void onActivityStarted  (Activity a) { onActStarted  (a); }
            public void onActivityResumed  (Activity a) { onActResumed  (a); }
            public void onActivityPaused   (Activity a) { onActPaused   (a); }
            public void onActivityStopped  (Activity a) { onActStopped  (a); }
            public void onActivityDestroyed(Activity a) { onActDestroyed(a); }
        });
    }

    private Activity mResumedActivity;

    private void onActCreated(Activity activity, Bundle savedInstanceState) {
        L.i("activity '%s' created", L.string(activity));
    }

    private void onActStarted(Activity activity) {
        L.i("activity '%s' started", L.string(activity));
    }

    private void onActResumed(Activity activity) {
        L.i("activity '%s' resumed", L.string(activity));

        mResumedActivity = activity;
        L.i("resumed activity is '%s'", L.string(mResumedActivity));
    }

    private void onActPaused(Activity activity) {
        L.i("activity '%s' paused", L.string(activity));

        if (mResumedActivity == activity) {
            mResumedActivity = null;
            L.i("resumed activity reset null");
        }
    }

    private void onActStopped(Activity activity) {
        L.i("activity '%s' stopped", L.string(activity));
    }

    private void onActSaveInstanceState(Activity activity, Bundle outState) {
        L.i("activity '%s' saveState", L.string(activity));
    }

    private void onActDestroyed(Activity activity) {
        L.i("activity '%s' Destroyed", L.string(activity));
    }

    //start activity

    private static final String ANIMATION_DEFAULT = "animation_default";
    private static final String ANIMATION_FADE    = "animation_fade";

    public void startActivity(String action, Bundle extras) {
        startActivityWithAnimation(ANIMATION_DEFAULT, action, extras);
    }

    public void startActivityWithFade(String action, Bundle extras) {
        startActivityWithAnimation(ANIMATION_FADE, action, extras);
    }

    private void startActivityWithAnimation(String animation, String action, Bundle extras) {
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
            L.i("start activity with animation '%s'", animation);
            if (animation.equals(ANIMATION_FADE)) {
                int entry = android.R.anim.fade_in;
                int exit = android.R.anim.fade_out;
                mResumedActivity.overridePendingTransition(entry, exit);
            }
        } catch (ActivityNotFoundException e) {
            L.e("activity not found: %s", e.toString());
        }
    }

    //move to background

    public void moveTaskToBackground() {
        if (mResumedActivity == null) {
            L.e("there isn't resumed activity currently, app already in background");
            return;
        }
        mResumedActivity.moveTaskToBack(true);
    }
}
