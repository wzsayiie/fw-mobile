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
        notifyDefaultWindowCreated(hashCode());
        notifyLoad(hashCode());
    }

    @Override
    protected void onStart() {
        super.onStart();
        notifyShow(hashCode());
    }

    @Override
    protected void onStop() {
        super.onStop();
        notifyHide(hashCode());
    }

    private native void notifyDefaultWindowCreated(long index);

    private native void notifyLoad(long index);
    private native void notifyShow(long index);
    private native void notifyHide(long index);

    @Override
    public boolean onTouchEvent(MotionEvent event) {

        int   h = hashCode();
        float s = _cq_window_get_screen_scale(h);
        float x = event.getX() / s;
        float y = event.getY() / s;

        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN  : notifyTouchBegan(h, x, y); break;
            case MotionEvent.ACTION_MOVE  : notifyTouchMoved(h, x, y); break;
            case MotionEvent.ACTION_UP    : notifyTouchEnded(h, x, y); break;
            case MotionEvent.ACTION_CANCEL: notifyTouchEnded(h, x, y); break;
        }
        return true;
    }

    private native void notifyTouchBegan(long index, float x, float y);
    private native void notifyTouchMoved(long index, float x, float y);
    private native void notifyTouchEnded(long index, float x, float y);

    private static float range(float min, float v, float max) {
        return v < min ? min : (v > max ? max : v);
    }

    public static void _cq_window_set_back_color(long index, float r, float g, float b) {
        CPPActivity activity = sharedActivityWithHash(index);
        if (activity == null) {
            return;
        }

        int ir = (int)(255 * range(0.f, r, 1.f));
        int ig = (int)(255 * range(0.f, g, 1.f));
        int ib = (int)(255 * range(0.f, b, 1.f));
        activity.mContentView.setBackgroundColor((0xff << 24) | (ir << 16) | (ig << 8) | ib);
    }

    public static float _cq_window_get_width(long index) {
        CPPActivity activity = sharedActivityWithHash(index);
        if (activity == null) {
            return 0;
        }

        Display display = activity.getWindowManager().getDefaultDisplay();
        DisplayMetrics metrics = new DisplayMetrics();
        display.getMetrics(metrics);

        return ((float) metrics.widthPixels) / metrics.density;
    }

    public static float _cq_window_get_height(long index) {
        CPPActivity activity = sharedActivityWithHash(index);
        if (activity == null) {
            return 0;
        }

        Display display = activity.getWindowManager().getDefaultDisplay();
        DisplayMetrics metrics = new DisplayMetrics();
        display.getMetrics(metrics);

        return ((float) metrics.heightPixels) / metrics.density;
    }

    public static float _cq_window_get_screen_scale(long index) {
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
