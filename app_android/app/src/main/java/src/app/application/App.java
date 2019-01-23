package src.app.application;

import android.app.Application;

import src.app.utility.application.AppDelegate;
import src.app.utility.application.CrashListener;
import src.app.utility.application.L;
import src.app.utility.data.AppInfo;

public class App extends Application {

    @Override
    public void onCreate() {
        super.onCreate();

        //remember app context, logging and crash listening,
        //they are so important, do them firstly.
        AppDelegate.initApp(this);
        L.i("test info log if available");
        L.e("test error log if available");
        if (CrashListener.get().lastLaunchCrashed()) {
            L.i("last launch crashed");
            //send crash info and log to the server
        }

        //startup different app delegate for different process type
        String processName = AppInfo.get().getProcessName();
        String packageName = AppInfo.get().getPackageName();
        if (processName.equals(packageName)) {

            L.i("ui process launches, process name '%s'", processName);
            MainAppDelegate.get().init();

        } else {

            L.i("service process launches, process name '%s'", processName);
            ServiceAppDelegate.get().init();
        }
    }
}
