package src.app.host.lua;

import android.app.Activity;
import android.os.Bundle;

public class LuaActivity extends Activity {

    static {
        System.loadLibrary("cargo");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        handleCreate();
    }

    @Override
    protected void onStart() {
        super.onStart();
        handleStart();
    }

    @Override
    protected void onStop() {
        super.onStop();
        handleStop();
    }

    private native void handleCreate();
    private native void handleStart();
    private native void handleStop();
}
