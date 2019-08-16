package src.app.mod;

import android.app.Application;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Build;

import src.app.boot.AppWrapper;
import src.library.foundation.L;

public class ServiceAssist {

    public static void startServiceIfNeeded(Class<?> clazz) {
        if (clazz == null) {
            L.e("try start service but the class is null");
            return;
        }

        Application app = AppWrapper.getApp();
        Intent intent = new Intent(app, clazz);

        ComponentName component;
        if (Build.VERSION.SDK_INT >= AndroidVersion.O_8_API_26) {
            //background service is not allowed.
            component = app.startForegroundService(intent);
        } else {
            component = app.startService(intent);
        }

        if (component != null) {
            L.i("start the service '%s' successful", clazz.getName());
        } else {
            L.e("start the service '%s' failed", clazz.getName());
        }
    }

    public static void bindService(Class<?> clazz, ServiceConnection connection) {
        if (clazz == null) {
            L.e("try start service but the class is null");
            return;
        }
        if (connection == null) {
            L.e("try bind service with a null connection");
            return;
        }

        Application app = AppWrapper.getApp();
        Intent intent = new Intent(app, clazz);
        app.bindService(intent, connection, 0);
    }

    public static void unbindService(ServiceConnection connection) {
        if (connection == null) {
            L.e("try unbind a service with a null connection");
            return;
        }

        Application app = AppWrapper.getApp();
        app.unbindService(connection);
    }

    public static void stopService(Class<?> clazz) {
        if (clazz == null) {
            L.e("try stop service but the class is null");
            return;
        }

        Application app = AppWrapper.getApp();
        Intent intent = new Intent(app, clazz);
        app.stopService(intent);
    }
}
