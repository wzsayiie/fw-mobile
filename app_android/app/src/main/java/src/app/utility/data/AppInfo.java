package src.app.utility.data;

import android.app.ActivityManager;
import android.app.Application;
import android.content.Context;
import android.os.Process;

import src.app.utility.application.AppDelegate;
import src.app.utility.application.L;
import src.app.utility.application.SingletonManager;

public class AppInfo {

    public static AppInfo get() {
        return SingletonManager.get().getInstanceOf(AppInfo.class);
    }

    public String getProcessName() {
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

    public String getPackageName() {
        return AppDelegate.getApp().getPackageName();
    }
}
