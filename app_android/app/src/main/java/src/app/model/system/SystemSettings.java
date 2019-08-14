package src.app.model.system;

public class SystemSettings {

    private static class Singleton {
        static SystemSettings instance = new SystemSettings();
    }
    public static SystemSettings get() {
        return Singleton.instance;
    }
}
