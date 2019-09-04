package src.app.model.system;

import src.library.basis.W;

@SuppressWarnings({W.APP_OMIT_0, W.APP_OMIT_1, W.APP_OMIT_2, W.APP_OMIT_3})
public class SystemSettings {

    private static class Singleton {
        static SystemSettings instance = new SystemSettings();
    }
    public static SystemSettings get() {
        return Singleton.instance;
    }
}
