package src.app.host.lua;

import android.app.Activity;
import android.os.Bundle;

import java.io.File;

public class LuaActivity extends Activity {

    static {
        System.loadLibrary("cargo");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        String luaPathString = getCacheDir().toString() + "/LUA";
        File luaPath = new File(luaPathString);
        if (!luaPath.exists()) {
            luaPath.mkdir();
        }
        handleCreate(luaPath.getPath());
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

    private native void handleCreate(String path);
    private native void handleStart();
    private native void handleStop();
}
