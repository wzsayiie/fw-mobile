package src.app.application;

public class ServiceAppDelegate extends CQAppDelegate {

    static ServiceAppDelegate get() {
        return CQSingletonManager.get().getInstanceOf(ServiceAppDelegate.class);
    }

    @Override
    protected void onCreate() {
    }
}
