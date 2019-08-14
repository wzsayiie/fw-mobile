package src.app.bootstrap;

import android.app.Application;
import android.os.Build;

import src.app.boot.AppWrapper;
import src.app.boot.CrashListener;
import src.app.mod.AppInfo;
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
        AppWrapper.assignApp(this);
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
        L.i("  process name : %s", AppInfo.getProcessName());
        L.i("  app version  : %s", AppInfo.getAppVersion());
        L.i("  android id   : %s", AppInfo.getAndroidID());
        L.i("}");

        String packageName = AppInfo.getPackageName();
        String processName = AppInfo.getProcessName();
        if (packageName.equals(processName)) {
            MainAppWrapper.get();
        } else {
            TaskAppWrapper.get();
        }
    }
}
