package src.app.application;

import android.app.Application;
import android.os.Build;

import src.app.utility.application.AppDelegate;
import src.app.utility.application.CrashListener;
import src.app.utility.data.AppInfo;
import src.library.foundation.L;

public class App extends Application {

    @Override
    public void onCreate() {
        super.onCreate();

        //save app context, test logging and crash listening.
        //they are so important, do them firstly.
        AppDelegate.initApp(this);
        L.i("test info log if available");
        L.e("test error log if available");
        if (CrashListener.get().lastLaunchCrashed()) {
            L.i("last launch crashed");
        }

        L.i("app created {");
        L.i("  manufacturer : %s", Build.MANUFACTURER);
        L.i("  hardware type: %s", Build.MODEL);
        L.i("  supported abi: %s", AppInfo.getSupportedABIs());
        L.i("  os version   : %s", Build.VERSION.RELEASE);
        L.i("  api level    : %d", Build.VERSION.SDK_INT);
        L.i("  process name : %s", AppInfo.getPackageName());
        L.i("  app version  : %s", AppInfo.getAppVersion());
        L.i("  android id   : %s", AppInfo.getAndroidID());
        L.i("}");

        L.i("ui process launches");
        MainAppDelegate.get().init();
    }
}
