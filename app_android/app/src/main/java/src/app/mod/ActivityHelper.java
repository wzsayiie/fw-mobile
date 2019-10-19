package src.app.mod;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.Application;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.os.Bundle;

import androidx.annotation.NonNull;

import src.app.boot.AppWrapper;
import src.library.basis.StringUtil;
import src.library.basis.W;
import src.library.foundation.L;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
public class ActivityHelper {

    private static class Singleton {
        @SuppressLint("StaticFieldLeak")
        static ActivityHelper instance = new ActivityHelper();
    }
    public static ActivityHelper get() {
        return Singleton.instance;
    }

    //subsystems can find current resumed activity dynamically by this method.
    public static Activity currentResumedActivity() {
        return get().mResumedActivity;
    }

    //activity lifecycle:

    private ActivityHelper() {

        AppWrapper.getApp().registerActivityLifecycleCallbacks(new Application.ActivityLifecycleCallbacks() {

            public void onActivitySaveInstanceState(@NonNull Activity a, @NonNull Bundle b) {
                onActSaveInstanceState(a);
            }
            public void onActivityCreated(@NonNull Activity a, Bundle b) {
                onActCreated(a);
            }

            public void onActivityStarted  (@NonNull Activity a) { onActStarted  (a); }
            public void onActivityResumed  (@NonNull Activity a) { onActResumed  (a); }
            public void onActivityPaused   (@NonNull Activity a) { onActPaused   (a); }
            public void onActivityStopped  (@NonNull Activity a) { onActStopped  (a); }
            public void onActivityDestroyed(@NonNull Activity a) { onActDestroyed(a); }
        });
    }

    private Activity mResumedActivity;

    private void onActCreated(Activity activity) {
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

    private void onActSaveInstanceState(Activity activity) {
        L.i("activity '%s' saveState", L.string(activity));
    }

    private void onActDestroyed(Activity activity) {
        L.i("activity '%s' Destroyed", L.string(activity));
    }

    //start activity:

    public static final int REQUEST_CODE = 100;
    public static final int RESULT_CODE = 100;

    private static final String ANIMATION_DEFAULT = "animation_default";
    private static final String ANIMATION_FADE    = "animation_fade";

    public void startActivity(String action, Bundle extras) {
        startActivityWithAnimation(ANIMATION_DEFAULT, action, extras);
    }

    public void startActivityWithFade(String action, Bundle extras) {
        startActivityWithAnimation(ANIMATION_FADE, action, extras);
    }

    private void startActivityWithAnimation(String animation, String action, Bundle extras) {
        if (StringUtil.isEmpty(action)) {
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
            mResumedActivity.startActivityForResult(intent, REQUEST_CODE);
            L.i("start activity with animation '%s'", animation);
            if (animation.equals(ANIMATION_FADE)) {
                int entryAnim = android.R.anim.fade_in;
                int exitAnim = android.R.anim.fade_out;
                mResumedActivity.overridePendingTransition(entryAnim, exitAnim);
            }
        } catch (ActivityNotFoundException e) {
            L.e("activity not found: %s", e.toString());
        }
    }

    //stop activity:

    public void finishActivity(Activity activity, Bundle extras) {
        finishActivityWithAnimation(ANIMATION_DEFAULT, activity, extras);
    }

    public void finishActivityWithFade(Activity activity, Bundle extras) {
        finishActivityWithAnimation(ANIMATION_FADE, activity, extras);
    }

    private void finishActivityWithAnimation(String animation, Activity activity, Bundle extras) {
        if (activity == null) {
            L.e("try finish a null activity");
            return;
        }

        //result data.
        Intent data = new Intent();
        if (extras != null) {
            data.putExtras(extras);
        }
        activity.setResult(RESULT_CODE, data);

        //finish with animation.
        activity.finish();
        L.i("finish activity with animation '%s'", animation);

        if (animation.equals(ANIMATION_FADE)) {
            int entryAnim = android.R.anim.fade_in;
            int exitAnim = android.R.anim.fade_out;
            activity.overridePendingTransition(entryAnim, exitAnim);
        }
    }
}
