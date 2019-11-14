package src.library.foundation;

import android.app.Activity;

import java.lang.reflect.Field;
import java.lang.reflect.Method;

import src.library.basis.W;

//NOTE: UIContextAssist only be used on main thread.

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class UIContextAssist {

    private static Activity currentCustomActivity() {
        try {
            Class<?> clazz = Class.forName("src.library.glkit.GLActivity");
            Method method = clazz.getMethod("sharedInstance");
            return (Activity) method.invoke(clazz);
        } catch (Exception e) {
            return null;
        }
    }

    private static Activity currentUnityActivity() {
        try {
            Class clazz = Class.forName("com.unity3d.player.UnityPlayer");
            Field field = clazz.getField("currentActivity");
            return (Activity) field.get(null);
        } catch (Exception e) {
            return null;
        }
    }

    private static Activity currentFWActivity() {
        try {
            Class<?> clazz = Class.forName("src.app.mod.ActivityHelper");
            Method method = clazz.getMethod("currentResumedActivity");
            return (Activity) method.invoke(clazz);
        } catch (Exception e) {
            return null;
        }
    }

    public static Activity currentActivity() {

        Activity target;

        //NOTE: call currentFWActivity() at the last, it will create some extra objects.
        target = currentCustomActivity();
        if (target != null) {
            return target;
        }

        target = currentUnityActivity();
        if (target != null) {
            return target;
        }

        return currentFWActivity();
    }
}
