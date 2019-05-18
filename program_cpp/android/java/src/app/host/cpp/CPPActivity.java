package src.app.host.cpp;

import android.app.Activity;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.Display;
import android.view.MotionEvent;
import android.view.View;

public class CPPActivity extends Activity {

    static {
        System.loadLibrary("cargo");
    }

    private static CPPActivity sSharedActivity = null;

    private static CPPActivity resetSharedActivity(CPPActivity activity, boolean reset) {
        if (reset) {
            sSharedActivity = activity;
        }
        return sSharedActivity;
    }

    private static CPPActivity sharedActivityWithHash(long hash) {
        //there is one activity on android, return shared object if 'hash' != 0.
        return hash != 0 ? resetSharedActivity(null, false) : null;
    }

    private View mContentView = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mContentView = new View(this);
        setContentView(mContentView);

        resetSharedActivity(this, true);
        onCreate(hashCode());
    }

    @Override
    protected void onStart() {
        super.onStart();

        onStart(hashCode());
    }

    @Override
    protected void onStop() {
        super.onStop();

        onStop(hashCode());
    }

    private native void onCreate(long index);
    private native void onStart(long index);
    private native void onStop(long index);

    @Override
    public boolean onTouchEvent(MotionEvent event) {

        Display display = getWindowManager().getDefaultDisplay();
        DisplayMetrics metrics = new DisplayMetrics();
        display.getMetrics(metrics);

        float x = event.getX() / metrics.density;
        float y = event.getY() / metrics.density;

        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN  : onTouchBegan(hashCode(), x, y); break;
            case MotionEvent.ACTION_MOVE  : onTouchMoved(hashCode(), x, y); break;
            case MotionEvent.ACTION_UP    : onTouchEnded(hashCode(), x, y); break;
            case MotionEvent.ACTION_CANCEL: onTouchEnded(hashCode(), x, y); break;
        }
        return true;
    }

    private native void onTouchBegan(long index, float x, float y);
    private native void onTouchMoved(long index, float x, float y);
    private native void onTouchEnded(long index, float x, float y);

    private static float range(float min, float v, float max) {
        return v < min ? min : (v > max ? max : v);
    }

    public static void window_set_back_color(long index, float r, float g, float b) {
        CPPActivity activity = sharedActivityWithHash(index);
        if (activity == null) {
            return;
        }

        int ir = (int)(255 * range(0.f, r, 1.f));
        int ig = (int)(255 * range(0.f, g, 1.f));
        int ib = (int)(255 * range(0.f, b, 1.f));
        activity.mContentView.setBackgroundColor((0xff << 24) | (ir << 16) | (ig << 8) | ib);
    }

    public static float window_get_width(long index) {
        CPPActivity activity = sharedActivityWithHash(index);
        if (activity == null) {
            return 0;
        }

        Display display = activity.getWindowManager().getDefaultDisplay();
        DisplayMetrics metrics = new DisplayMetrics();
        display.getMetrics(metrics);

        return ((float) metrics.widthPixels) / metrics.density;
    }

    public static float window_get_height(long index) {
        CPPActivity activity = sharedActivityWithHash(index);
        if (activity == null) {
            return 0;
        }

        Display display = activity.getWindowManager().getDefaultDisplay();
        DisplayMetrics metrics = new DisplayMetrics();
        display.getMetrics(metrics);

        return ((float) metrics.heightPixels) / metrics.density;
    }

    public static float window_get_screen_scale(long index) {
        CPPActivity activity = sharedActivityWithHash(index);
        if (activity == null) {
            return 0;
        }

        Display display = activity.getWindowManager().getDefaultDisplay();
        DisplayMetrics metrics = new DisplayMetrics();
        display.getMetrics(metrics);
        return metrics.density;
    }
}
