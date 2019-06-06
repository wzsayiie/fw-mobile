package src.app.host.lua;

import src.app.host.basis.HostActivity;

public class LuaHostActivity extends HostActivity {

    @Override
    public void onGLViewLoad(int width, int height) {
        super.onGLViewLoad(width, height);
        entry();
    }

    protected native void entry();
}
