package src.app.application;

import src.app.data.CQActivityDispatcher;

public class MainAppDelegate extends CQAppDelegate {

    static MainAppDelegate get() {
        return CQSingletonManager.get().getInstanceOf(MainAppDelegate.class);
    }

    @Override
    public void onCreate() {
        CQActivityDispatcher.get();
    }
}
