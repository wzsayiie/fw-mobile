package src.app.host.cpp;

import android.app.Activity;
import android.os.Bundle;

import src.library.foundation.L;

public class CPPActivity extends Activity {

    static {
        System.loadLibrary("cargo");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        L.i("Android Host: activity create() enter");
        handleCreate();
        L.i("Android Host: activity create() exit");
    }

    @Override
    protected void onStart() {
        super.onStart();

        L.i("Android Host: activity start() enter");
        handleStart();
        L.i("Android Host: activity start() exit");
    }

    @Override
    protected void onStop() {
        super.onStop();

        L.i("Android Host: activity stop() enter");
        handleStop();
        L.i("Android Host: activity stop() exit");
    }

    private native void handleCreate();
    private native void handleStart();
    private native void handleStop();
}
