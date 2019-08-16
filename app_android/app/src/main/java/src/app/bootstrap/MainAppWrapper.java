package src.app.bootstrap;

import android.os.Build;

import src.app.boot.AppWrapper;
import src.app.boot.CrashListener;
import src.app.mod.ActivityHelper;
import src.app.mod.AppInfo;
import src.app.mod.HotfixHelper;
import src.library.foundation.L;

public class MainAppWrapper extends AppWrapper {

    private static class Singleton {
        static MainAppWrapper instance = new MainAppWrapper();
    }
    public static MainAppWrapper get() {
        return Singleton.instance;
    }

    private MainAppWrapper() {
        L.i("main app {");
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

        CrashListener.get();
        HotfixHelper.get();
        ActivityHelper.get();
    }
}
