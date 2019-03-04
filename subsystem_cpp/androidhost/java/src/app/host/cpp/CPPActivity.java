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
        L.i("Android Host: Activity onCreate");

        handleCreate();
    }

    @Override
    protected void onStart() {
        super.onStart();
        L.i("Android Host: Activity onStart");

        handleStart();
    }

    @Override
    protected void onStop() {
        super.onStop();
        L.i("Android Host: Activity onStop");

        handleStop();
    }

    private native void handleCreate();
    private native void handleStart();
    private native void handleStop();
}
