package src.app.bootstrap;

import src.app.boot.AppWrapper;
import src.app.mod.AppInfo;
import src.library.basis.W;
import src.library.foundation.L;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
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
