package src.app.bootstrap;

import android.app.Application;

import src.app.boot.AppWrapper;
import src.app.mod.AppInfo;

public class App extends Application {

    static {
        System.loadLibrary("library");
    }
    
    @Override
    public void onCreate() {
        super.onCreate();

        //saving app context fot the first time,
        //it will be used by other parts.
        AppWrapper.assignApp(this);

        String packageName = AppInfo.getPackageName();
        String processName = AppInfo.getProcessName();
        if (packageName.equals(processName)) {
            MainAppWrapper.get();
        } else {
            TaskAppWrapper.get();
        }
    }
}
