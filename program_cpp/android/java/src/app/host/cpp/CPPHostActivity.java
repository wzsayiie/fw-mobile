package src.app.host.cpp;

import src.app.host.HostActivity;

public class CPPHostActivity extends HostActivity {

    @Override
    public void onGLViewLoad(int width, int height) {
        super.onGLViewLoad(width, height);
        entry();
    }

    protected native void entry();
}
