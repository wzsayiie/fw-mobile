package src.app.bootstrap;

import src.app.boot.AppWrapper;
import src.app.mod.AppInfo;
import src.library.foundation.L;

public class TaskAppWrapper extends AppWrapper {

    private static class Singleton {
        static TaskAppWrapper instance = new TaskAppWrapper();
    }
    public static TaskAppWrapper get() {
        return Singleton.instance;
    }

    private TaskAppWrapper() {
        L.i("task app {");
        L.i("  process name: %s", AppInfo.getProcessName());
        L.i("}");
    }
}
