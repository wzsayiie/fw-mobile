package src.app.utility.data;

import android.app.ActivityManager;
import android.app.Application;
import android.content.ContentResolver;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Process;
import android.provider.Settings;
import android.text.TextUtils;

import src.app.utility.application.AppDelegate;
import src.app.utility.application.L;

public class AppInfo {

    public static String getProcessName() {
        Application app = AppDelegate.getApp();
        ActivityManager manager = (ActivityManager) app.getSystemService(Context.ACTIVITY_SERVICE);
        if (manager == null) {
            L.e("activity service did not found");
            return "";
        }

        int pid = Process.myPid();
        for (ActivityManager.RunningAppProcessInfo info : manager.getRunningAppProcesses()) {
            if (info.pid == pid) {
                return info.processName;
            }
        }
        L.e("current pid didn't match any process name");
        return "";
    }

    public static String getPackageName() {
        return AppDelegate.getApp().getPackageName();
    }

    public static String getAppVersion() {
        try {
            PackageManager manager = AppDelegate.getApp().getPackageManager();
            String packageName = getPackageName();
            PackageInfo info = manager.getPackageInfo(packageName, 0);
            return info.versionName;
        } catch (PackageManager.NameNotFoundException e) {
            L.e("exception on get app version: %s", e.toString());
            return "";
        }
    }

    public static String getAndroidID() {
        ContentResolver resolver = AppDelegate.getApp().getContentResolver();
        return Settings.System.getString(resolver, Settings.Secure.ANDROID_ID);
    }

    public static String getSupportedABIs() {
        if (Build.VERSION.SDK_INT >= 21) {
            String[] values = Build.SUPPORTED_ABIS;
            return TextUtils.join("|", values);
        } else {
            String abi1 = Build.CPU_ABI;
            String abi2 = Build.CPU_ABI2;
            return abi2 != null ? abi1 + "|" + abi2 : abi1;
        }
    }
}
