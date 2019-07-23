package src.app.host.lua;

import src.app.host.basis.HostActivity;

public class LuaHostActivity extends HostActivity {

    @Override
    public void invokeEntry() {
        entry();
    }

    protected native void entry();
}
