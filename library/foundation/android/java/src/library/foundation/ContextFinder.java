package src.library.foundation;

import android.app.Activity;
import android.app.Application;

import java.lang.reflect.Method;

public class ContextFinder {

    private static ContextFinder sInstance;

    public static ContextFinder get() {
        if (sInstance == null) {
            sInstance = new ContextFinder();
        }
        return sInstance;
    }

    private Activity findCustomAppActivity() {
        try {
            Class<?> clazz = Class.forName("src.app.host.HostActivity");
            Method method = clazz.getMethod("sharedInstance");
            return (Activity) method.invoke(clazz);
        } catch (Exception e) {
            return null;
        }
    }

    private Activity findUnity3DAppActivity() {
        return null;
    }

    private Activity findFrameworkAppActivity() {
        try {
            Class<?> clazz = Class.forName("src.app.data.CQActivityDispatcher");
            Method method = clazz.getMethod("currentResumedActivity");
            return (Activity) method.invoke(clazz);
        } catch (Exception e) {
            return null;
        }
    }

    public Activity findCurrentActivity() {

        Activity target;

        target = findCustomAppActivity   (); if (target != null) { return target; }
        target = findUnity3DAppActivity  (); if (target != null) { return target; }
        target = findFrameworkAppActivity(); if (target != null) { return target; }

        return null;
    }

    public Application findApplication() {
        Activity activity = findCurrentActivity();
        if (activity != null) {
            return activity.getApplication();
        } else {
            return null;
        }
    }
}
