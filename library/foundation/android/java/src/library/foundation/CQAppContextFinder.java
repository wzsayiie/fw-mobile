package src.library.foundation;

import android.app.Activity;
import android.app.Application;

import java.lang.reflect.Field;
import java.lang.reflect.Method;

public class CQAppContextFinder {

    private static class Singleton {
        static CQAppContextFinder instance = new CQAppContextFinder();
    }
    public static CQAppContextFinder get() {
        return Singleton.instance;
    }

    private Application findCustomApp() {
        try {
            Class<?> clazz = Class.forName("src.app.host.basis.HostActivity");
            Method method = clazz.getMethod("sharedInstance");
            Activity activity = (Activity) method.invoke(clazz);
            return activity.getApplication();
        } catch (Exception e) {
            return null;
        }
    }

    private Application findUnity3DApp() {
        try {
            Class clazz = Class.forName("com.unity3d.player.UnityPlayer");
            Field field = clazz.getField("currentActivity");
            Activity activity = (Activity) field.get(null);
            return activity.getApplication();
        } catch (Exception e) {
            return null;
        }
    }

    private Application findFrameworkApp() {
        try {
            Class<?> clazz = Class.forName("src.app.application.CQAppDelegate");
            Method method = clazz.getMethod("getApp");
            return (Application) method.invoke(clazz);
        } catch (Exception e) {
            return null;
        }
    }

    public Application findApp() {

        Application target;

        target = findCustomApp   (); if (target != null) { return target; }
        target = findUnity3DApp  (); if (target != null) { return target; }
        target = findFrameworkApp(); if (target != null) { return target; }

        return null;
    }
}
