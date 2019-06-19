package src.app.application;

public class ServiceAppDelegate extends CQAppDelegate {

    private static ServiceAppDelegate sInstance;

    static synchronized ServiceAppDelegate get() {
        if (sInstance == null) {
            sInstance = new ServiceAppDelegate();
        }
        return sInstance;
    }

    @Override
    protected void onCreate() {
    }
}
