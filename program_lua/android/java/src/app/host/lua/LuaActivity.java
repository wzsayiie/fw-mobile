package src.app.host.lua;

import android.app.Activity;
import android.os.Bundle;

import java.io.File;

import src.library.foundation.L;

public class LuaActivity extends Activity {

    static {
        System.loadLibrary("cargo");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        L.i("host: on create");

        onCreate(hashCode());
    }

    @Override
    protected void onStart() {
        super.onStart();
        L.i("host: on start");

        onStart(hashCode());
    }

    @Override
    protected void onStop() {
        super.onStop();
        L.i("host: on stop");

        onStop(hashCode());
    }

    private native void onCreate(long index);
    private native void onStart(long index);
    private native void onStop(long index);
}
