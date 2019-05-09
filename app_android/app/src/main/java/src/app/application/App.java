package src.app.application;

import android.app.Application;
import android.os.Build;

import src.app.data.CQAppInfo;
import src.library.foundation.L;

public class App extends Application {

    @Override
    public void onCreate() {
        super.onCreate();

        //save app context, test logging and crash listening.
        //they are so important, do them firstly.
        CQAppDelegate.initApp(this);
        L.i("test if info log is available");
        L.e("test if error log is available");
        if (CQCrashListener.get().lastLaunchCrashed()) {
            L.i("last launch crashed");
        }

        L.i("app created {");
        L.i("  manufacturer : %s", Build.MANUFACTURER);
        L.i("  hardware type: %s", Build.MODEL);
        L.i("  supported abi: %s", CQAppInfo.getSupportedABIs());
        L.i("  os version   : %s", Build.VERSION.RELEASE);
        L.i("  api level    : %d", Build.VERSION.SDK_INT);
        L.i("  process name : %s", CQAppInfo.getPackageName());
        L.i("  app version  : %s", CQAppInfo.getAppVersion());
        L.i("  android id   : %s", CQAppInfo.getAndroidID());
        L.i("}");

        L.i("ui process launches");
        MainAppDelegate.get().init();
    }
}
