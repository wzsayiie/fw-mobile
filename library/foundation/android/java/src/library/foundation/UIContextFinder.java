package src.library.foundation;

import android.app.Activity;

import java.lang.reflect.Field;
import java.lang.reflect.Method;

//NOTE: UIContextFinder only be used on main thread.

public class UIContextFinder {

    private static class Singleton {
        static UIContextFinder instance = new UIContextFinder();
    }
    public static UIContextFinder get() {
        return Singleton.instance;
    }

    private Activity findCustomAppActivity() {
        try {
            Class<?> clazz = Class.forName("src.app.host.basis.HostActivity");
            Method method = clazz.getMethod("sharedInstance");
            return (Activity) method.invoke(clazz);
        } catch (Exception e) {
            return null;
        }
    }

    private Activity findUnity3DAppActivity() {
        try {
            Class clazz = Class.forName("com.unity3d.player.UnityPlayer");
            Field field = clazz.getField("currentActivity");
            return (Activity) field.get(null);
        } catch (Exception e) {
            return null;
        }
    }

    private Activity findFrameworkAppActivity() {
        try {
            Class<?> clazz = Class.forName("src.app.com.ActivityDispatcher");
            Method method = clazz.getMethod("currentResumedActivity");
            return (Activity) method.invoke(clazz);
        } catch (Exception e) {
            return null;
        }
    }

    public Activity findCurrentActivity() {

        Activity target;

        //NOTE:
        //call findFrameworkAppActivity() at the last,
        //it will create some extra objects.

        target = findCustomAppActivity   (); if (target != null) { return target; }
        target = findUnity3DAppActivity  (); if (target != null) { return target; }
        target = findFrameworkAppActivity(); if (target != null) { return target; }

        return null;
    }
}
