package src.library.foundation;

import android.app.Activity;
import android.app.Application;

import java.lang.reflect.Field;
import java.lang.reflect.Method;

import src.library.basis.W;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class AppContextAssist {

    private static Application getCustomApp() {
        try {
            Class<?> clazz = Class.forName("src.library.glkit.GLActivity");
            Method method = clazz.getMethod("sharedInstance");
            Activity activity = (Activity) method.invoke(clazz);
            return activity.getApplication();
        } catch (Exception e) {
            return null;
        }
    }

    private static Application getUnityApp() {
        try {
            Class clazz = Class.forName("com.unity3d.player.UnityPlayer");
            Field field = clazz.getField("currentActivity");
            Activity activity = (Activity) field.get(null);
            return activity.getApplication();
        } catch (Exception e) {
            return null;
        }
    }

    private static Application getFWApp() {
        try {
            Class<?> clazz = Class.forName("src.app.boot.AppWrapper");
            Method method = clazz.getMethod("getApp");
            return (Application) method.invoke(clazz);
        } catch (Exception e) {
            return null;
        }
    }

    public static Application getApp() {

        Application target;

        target = getCustomApp();
        if (target != null) {
            return target;
        }

        target = getUnityApp();
        if (target != null) {
            return target;
        }

        return getFWApp();
    }
}
