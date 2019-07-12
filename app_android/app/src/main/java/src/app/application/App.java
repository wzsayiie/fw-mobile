package src.app.application;

import android.app.Application;
import android.os.Build;

import src.app.application.cq.AppDelegate;
import src.app.application.cq.CrashListener;
import src.app.data.cq.AppInfo;
import src.library.foundation.L;

public class App extends Application {

    static {
        System.loadLibrary("library");
    }
    
    @Override
    public void onCreate() {
        super.onCreate();

        //save app context, test logging and crash listening.
        //they are so important, do them firstly.
        AppDelegate.initApp(this);
        L.i("test if info log is available");
        L.e("test if error log is available");
        if (CrashListener.get().lastLaunchCrashed()) {
            L.i("last launch crashed");
        }

        L.i("app created {");
        L.i("  manufacturer : %s", Build.MANUFACTURER);
        L.i("  hardware type: %s", Build.MODEL);
        L.i("  supported abi: %s", AppInfo.getSupportedABIs());
        L.i("  os version   : %s", Build.VERSION.RELEASE);
        L.i("  api level    : %d", Build.VERSION.SDK_INT);
        L.i("  apk sign sha1: %s", AppInfo.getApkSignatureDigest("SHA1"));
        L.i("  process name : %s", AppInfo.getPackageName());
        L.i("  app version  : %s", AppInfo.getAppVersion());
        L.i("  android id   : %s", AppInfo.getAndroidID());
        L.i("}");

        L.i("ui process launches");
        MainAppDelegate.get().init();
    }
}
