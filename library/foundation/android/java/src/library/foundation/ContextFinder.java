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

    private Application findFrameworkApp() {
        return null;
    }

    private Application findCustomCPPApp() {
        return null;
    }

    private Application findCustomLuaApp() {
        return null;
    }

    private Application findUnity3DApp() {
        return null;
    }

    public Application findApp() {

        Application target = null;

        target = findFrameworkApp(); if (target != null) { return target; }
        target = findCustomCPPApp(); if (target != null) { return target; }
        target = findCustomLuaApp(); if (target != null) { return target; }
        target = findUnity3DApp  (); if (target != null) { return target; }

        return target;
    }

    private Activity findFrameworkAppActivity() {
        try {
            Class<?> clazz = Class.forName("src.app.utility.data.ActivityDispatcher");
            Method method = clazz.getMethod("currentResumedActivity");
            return (Activity) method.invoke(clazz);
        } catch (Exception e) {
            return null;
        }
    }

    private Activity findCustomCPPAppActivity() {
        return null;
    }

    private Activity findCustomLuaAppActivity() {
        return null;
    }

    private Activity findUnity3DAppActivity() {
        return null;
    }

    public Activity findActivity() {

        Activity target = null;

        target = findFrameworkAppActivity(); if (target != null) { return target; }
        target = findCustomCPPAppActivity(); if (target != null) { return target; }
        target = findCustomLuaAppActivity(); if (target != null) { return target; }
        target = findUnity3DAppActivity  (); if (target != null) { return target; }

        return target;
    }
}
