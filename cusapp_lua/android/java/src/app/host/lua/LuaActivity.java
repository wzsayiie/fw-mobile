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

        String cachePath= getCacheDir().toString();
        File luaPath = new File(cachePath + "/LUA");
        if (!luaPath.exists()) {
            boolean succeed = luaPath.mkdir();
            if (!succeed) {
                L.e("host: failed to create lua directory");
            }
        }

        onCreate(luaPath.getPath(), hashCode());
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

    private native void onCreate(String path, long index);
    private native void onStart(long index);
    private native void onStop(long index);
}
