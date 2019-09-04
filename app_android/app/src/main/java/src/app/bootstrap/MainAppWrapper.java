package src.app.bootstrap;

import android.os.Build;

import src.app.boot.AppWrapper;
import src.app.boot.CrashListener;
import src.app.mod.ActivityHelper;
import src.app.mod.AppInfo;
import src.app.mod.HotfixHelper;
import src.app.mod.NetStatusHelper;
import src.library.basis.W;
import src.library.foundation.L;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
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

        Object ignored_0 = CrashListener.get();
        Object ignored_1 = HotfixHelper.get();
        Object ignored_2 = ActivityHelper.get();
        Object ignored_3 = NetStatusHelper.get();
    }
}
