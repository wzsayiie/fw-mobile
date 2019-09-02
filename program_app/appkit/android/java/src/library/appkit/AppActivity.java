package src.library.appkit;

import src.library.glkit.GLActivity;

public class AppActivity extends GLActivity {

    @Override
    public void invokeEntry() {
        entry();
    }

    protected native void entry();
}
