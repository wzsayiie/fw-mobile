package src.app.host.cpp;

import src.app.host.basis.HostActivity;

public class CPPHostActivity extends HostActivity {

    @Override
    public void invokeEntry() {
        entry();
    }

    protected native void entry();
}
