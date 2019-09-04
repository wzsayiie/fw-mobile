package src.library.appkit;

import src.library.basis.W;
import src.library.glkit.GLActivity;

@SuppressWarnings({W.LIB_OMIT_0, W.LIB_OMIT_1, W.LIB_OMIT_2, W.LIB_OMIT_3})
public class AppActivity extends GLActivity {

    @Override
    public void invokeEntry() {
        entry();
    }

    protected native void entry();
}
