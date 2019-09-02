package src.library.gamekit;

import src.library.glkit.GLActivity;

public class GameActivity extends GLActivity {

    @Override
    public void invokeEntry() {
        entry();
    }

    protected native void entry();
}
