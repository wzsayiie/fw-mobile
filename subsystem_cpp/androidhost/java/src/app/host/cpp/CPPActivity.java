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

        L.i("host: activity create() enter");
        handleCreate(this.hashCode());
        L.i("host: activity create() exit");
    }

    @Override
    protected void onStart() {
        super.onStart();

        L.i("host: activity start() enter");
        handleStart(this.hashCode());
        L.i("host: activity start() exit");
    }

    @Override
    protected void onStop() {
        super.onStop();

        L.i("host: activity stop() enter");
        handleStop(this.hashCode());
        L.i("host: activity stop() exit");
    }

    private native void handleCreate(long index);
    private native void handleStart(long index);
    private native void handleStop(long index);

    public static void _cq_window_set_back_color(long index, float r, float g, float b) {
        L.i("r = %f, g = %f, b = %f", r, g, b);
    }

    public static float _cq_window_get_width(long index) {
        return 0;
    }

    public static float _cq_window_get_height(long index) {
        return 0;
    }

    public static float _cq_window_get_screen_scale(long index) {
        return 0;
    }
}
